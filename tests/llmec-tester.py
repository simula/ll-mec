import threading
import time
import multiprocessing
import socket
import numpy
import config
import math
import requests
import json
from lib import gtp
from multiprocessing import *
from scapy.all import *

# IP <-> int
ip2int = lambda ipstr: struct.unpack('!I', socket.inet_aton(ipstr))[0]
int2ip = lambda n: socket.inet_ntoa(struct.pack('!I', n))

# Sockets
rev_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
rev_socket.bind(('', 2152))
send_socket = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
send_socket.bind((config.generator_interface,0))

def gtpv1_u_thread(index):
	while True:
		# Listen for UDP data
		data, (ip, port) = rev_socket.recvfrom(1024)
		# Make sure the socket is open and has returned valid results
		if not data:
			break
		# Spawn a new thread for the incoming packet
		thread.start_new_thread(handle_packet, (data, ip, port))

def handle_packet(packet, ip, port):
	# Decapsulate
	decap_data = gtp.decapsulate(packet)
	p = IP(decap_data['payload'])
	if ICMP in IP(decap_data['payload']):
		packet = Ether()/IP(src=p.src, dst=p.dst)/ICMP(type='echo-reply')
		#send_socket.send(str(packet))
		#send(packet, verbose=0)
	else:
		print("Unidentified packet coming")
		return

def send_data(index):
	start=time.clock()
	ans,unans = srp(ue_list[index], timeout=config.ping_timeout)
	end=time.clock()
	if not len(ans)==0:
		ue_time[index]+=(end-start)
		ue_counts[index]+=1

if __name__ == "__main__":
    # Construct UE context to send
    ue_list = []
    bearer_list = []
    imsi = 208950000000000
    start_ip = config.UE_IP_start
    ul_teid = config.SGW_TEID_start
    dl_teid = config.ENB_TEID_start
    enb_ip = config.generator_address
    for i in xrange(1, config.N_UE + 1):
        if i%100 == 0:
            print(start_ip, ul_teid)
        p = IP(src = config.UE_IP_start, dst = config.ping_dst)/ICMP()/Raw(' ' * int(config.ping_packet_size))
        p = gtp.encapsulate(str(p), config.SGW_TEID_start)['message']
        p = Ether()/IP(src = config.generator_address, dst = config.S1U_address)/UDP(sport = config.GTPv1_user_port, dport = config.GTPv1_user_port)/p
        ue_list.append(p)
        data = {'eps_bearer_id':5, 'imsi':str(imsi+i),  's1_ul_teid': str(ul_teid), 's1_dl_teid' : str(dl_teid), 'ue_ip': str(start_ip), 'enb_ip' : str(enb_ip)}
        print data
        bearer_list.append(data)
        # req = requests.post(url,json.dumps(data),headers={'Content-Type': 'application/x-www-form-urlencoded'})
        start_ip = int2ip(ip2int(start_ip) + 1)
        ul_teid = ul_teid + 1
        dl_teid = dl_teid + 1

    # Add bearer context
    url = 'http://' + config.llmec_address + ':' + config.llmec_northbound_port + '/bearer'
    for i in xrange(0, config.N_UE):
        req = requests.post(url, json.dumps(bearer_list[i]), headers={'Content-Type': 'application/x-www-form-urlencoded'})

    # Confirm bearer added
    base_url = 'http://' + config.llmec_address + ':' + config.llmec_northbound_port + '/bearer/imsi_bearer'
    for i in xrange(0, config.N_UE):
        url = base_url + '/' + bearer_list[i]['imsi'] + ',5'
        req = requests.get(url)
        if req.status_code == 200:
            response = req.json()
            if response != None:
                print("UE %d added\n" % (i))
            else:
                print("UE %d add failed\n" % (i))


    # Redirect bearer based on the redirect rate
    base_url = 'http://' + config.llmec_address + ':' + config.llmec_northbound_port + '/bearer/redirect'
    N_redirect_UE = int(math.floor(config.N_UE * config.redirect_rate))
    data = {"from":str(config.ping_dst), "to":str(config.generator_address)}
    for i in xrange(0, N_redirect_UE):
        url = base_url + '/imsi_bearer/' + bearer_list[i]['imsi'] + ',5'
        req = requests.post(url, json.dumps(data), headers={'Content-Type': 'application/x-www-form-urlencoded'})

    # Confirm if redirected
    base_url = 'http://' + config.llmec_address + ':' + config.llmec_northbound_port + '/bearer/imsi_bearer'
    N_redirect_UE = int(math.floor(config.N_UE * config.redirect_rate))
    for i in xrange(0, N_redirect_UE):
        url = base_url + '/' + bearer_list[i]['imsi'] + ',5'
        req = requests.get(url)
        if req.status_code == 200:
            response = req.json()
            if response['redirect']:
                print("UE %d redirected" % (i))
            else:
                print("UE %d redirected faile" % (i))

    # Packet sending process pool
    print("Start %d processes sending packets\n" % (config.number_of_sending_process))
    ue_time = multiprocessing.Array('f', config.N_UE)
    ue_counts = multiprocessing.Array('i', config.N_UE)
    pool = Pool(processes=config.number_of_sending_process)

    # Packet receiving threads
    print("Start %d threads receiving packets\n" % (config.number_of_receiving_thread))
    for i in xrange(0, config.number_of_receiving_thread):
        thread.start_new_thread(gtpv1_u_thread, (i,))

    # Generating traffic
    print("Start sending ICMP packets\n")
    for i in xrange(0, config.ping_counts):
        pool.map(send_data, range(config.N_UE))
        time.sleep(config.ping_interval)
        #Calculate results

    # Remove bearer context
    base_url = 'http://' + config.llmec_address + ':' + config.llmec_northbound_port + '/bearer'
    req = requests.delete(base_url)
    if req.status_code == 200:
        print("Bearer context deleted")

    # Calculating results
    total_counts = config.ping_counts * config.N_UE
    latency=0
    c=0
    data=[]
    for i in xrange(0, config.N_UE):
        if not ue_counts[i] == 0:
            latency = latency + (ue_time[i] / ue_counts[i])
            data.append(ue_time[i]/ue_counts[i])
            c = c + ue_counts[i]

    sdev = 0
    if data:
      sdev = numpy.std(data)

    # Outputing
    ping_file = open(config.log_output_file, 'w')
    ping_file.truncate()
    print("Average latency:%f, Ping drop: %f\n"%(latency/config.N_UE, float(total_counts-c)/float(total_counts)))
    ping_file.write("%f %f\n" % (latency*1000/config.N_UE, sdev/1000))
    ping_file.close()
    pool.terminate()
    pool.join()
