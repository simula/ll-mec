#!/usr/bin/python

# Numbers of UE
N_UE = 1

# Nodes address
generator_address = "192.168.12.242"
generator_interface = "enp3s0"
S1U_address = "10.10.10.1"

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
number_of_receiving_process = 1

# Log
log_output_file = "ue_traffic_generator.log"
