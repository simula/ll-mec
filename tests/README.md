LL-MEC tester 
======================================
## What is LL-MEC tester?
LL-MEC tester is developed to ease the testing.
* Developed in Python.
* Simulate to send the massive GTP traffic (One UE per process) at the same time.
* Test both for control and user plane

## Main Python library dependency
* scapy: to craft the packets
* multiprocessing: to create the process pool
* numpy: calculate the statistic

## Configuration example (config.py)

    # general settings
    N_UE = 1
    redirect_rate = 0.9

    # Nodes address
    generator_address = "192.168.111.1"
    generator_interface = "vboxnet0"
    S1U_address = "192.168.111.10"
    llmec_address = "127.0.0.1"
    llmec_northbound_port = "9999"

    # Interface ports
    GTPv1_user_port = 2152

    # UE info
    SGW_TEID_start = 1
    ENB_TEID_start = 200 # not being used for the moment
    UE_IP_start = "172.16.0.2"

    # Pinger settings
    ping_packet_size = 1400 # bytes
    ping_counts = 1
    ping_interval = 1 # seconds
    ping_timeout = 3
    ping_dst = "8.8.8.8"

    # Multi-process settings
    number_of_sending_process = 1
    number_of_receiving_thread = 1

    # Log
    log_output_file = "llmec-tester.log"

## Usage example
    $ sudo python llmec-tester.py
    
## Contact
Please email to Mosaic5G (mosaic5g@lists.eurecom.fr)
