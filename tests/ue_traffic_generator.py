import threading
import time
import multiprocessing
import socket
import numpy
import config
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
    START_IP = config.UE_IP_start
    TEID = config.SGW_TEID_start
    for i in range(config.N_UE):
        if i%100 == 0:
            print(START_IP, TEID)
        p = IP(src = config.UE_IP_start, dst = config.ping_dst)/ICMP()/Raw(' ' * int(config.ping_packet_size))
        p = gtp.encapsulate(str(p), config.SGW_TEID_start)['message']
        p = Ether()/IP(src = config.generator_address, dst = config.S1U_address)/UDP(sport = config.GTPv1_user_port, dport = config.GTPv1_user_port)/p
	ue_list.append(p)
	START_IP = int2ip(ip2int(START_IP) + 1)
	TEID = TEID + 1

    # Packet sending process pool
    print("Start %d processes sending packets\n" % (config.number_of_receiving_process))
    ue_time = multiprocessing.Array('f', config.N_UE)
    ue_counts = multiprocessing.Array('i', config.N_UE)
    pool = Pool(processes=config.number_of_sending_process)

    # Packet receiving threads
    print("Start %d threads receiving packets\n" % (config.number_of_receiving_process))
    for i in xrange(0, config.number_of_receiving_process):
        thread.start_new_thread(gtpv1_u_thread, (i,))

    # Generating traffic
    print("Start sending ICMP packets\n")
    for i in xrange(0, config.ping_counts):
        pool.map(send_data, range(config.N_UE))
        time.sleep(config.ping_interval)
        #Calculate results

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
