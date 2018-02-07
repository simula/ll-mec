#!/usr/bin/python

"""
Helper functions for GTP
"""

import random



teid = 0
def createTEID(r=True):

    if r == True:
        # Create a random TEID number with at max 2^32
        return random.randint(0, (pow(2, 32)-1))
    else:
        global teid
        teid = teid + 1
        return teid


def encapsulate(payload, teid):
    version = 1           # GTPv1 
    protocol_type = 1     # GTP
    reserved = 0
    ext_header_flag = 0
    seq_number_flag = 0
    npdu_number_flag = 0
    msg_type = 0xFF       # Regular payload type
    
    # Deterine the length of the payload in bytes
    msg_size = len(payload)

    # Construct the first part of the GTP header
    h =  version               << 29
    h += protocol_type         << 28
    h += reserved              << 27
    h += ext_header_flag       << 26
    h += seq_number_flag       << 25 
    h += npdu_number_flag      << 24
    h += msg_type              << 16
    h += msg_size              << 0

    # Shift over by 32 bit and add the TEID
    h = h << 32
    h += teid  << 0
        
    # Convert GTP header to character representation and add payload
    message =  chr((h & 0xFF00000000000000) >> 56)
    message += chr((h & 0x00FF000000000000) >> 48)
    message += chr((h & 0x0000FF0000000000) >> 40)
    message += chr((h & 0x000000FF00000000) >> 32)
    message += chr((h & 0x00000000FF000000) >> 24)
    message += chr((h & 0x0000000000FF0000) >> 16)
    message += chr((h & 0x000000000000FF00) >> 8)
    message += chr((h & 0x00000000000000FF) >> 0)
    header = message
    message += payload

    # Store into dict and return it
    gtp_dict = dict()
    gtp_dict['header'] = header
    gtp_dict['payload'] = payload
    gtp_dict['message'] = message
    return gtp_dict


    
def decapsulate(message):

    # Create the return dictionary
    gtp_dict = dict()

    # Convert the message to byte array
    message = bytearray(message)

    # Get the GTP header
    header = message[0:8]

    # Get the fields of the first 4 bytes
    gtp_dict['version'] =          (header[0] & 0xE0) >> 5 # 1110 0000
    gtp_dict['protocol_type'] =    (header[0] & 0x10) >> 4 # 0001 0000
    gtp_dict['ext_header_flag'] =  (header[0] & 0x04) >> 2 # 0000 0100
    gtp_dict['seq_number_flag'] =  (header[0] & 0x02) >> 1 # 0000 0010
    gtp_dict['npdu_number_flag'] = (header[0] & 0x01) >> 0 # 0000 0001
    gtp_dict['msg_type'] =         (header[1] & 0xFF) >> 0
    gtp_dict['msg_size'] =         ((header[2] & 0xFF) << 8) + \
                                   ((header[3] & 0xFF) << 0)
    gtp_dict['teid'] =             ((header[4] & 0xFF) << 24) + \
                                   ((header[5] & 0xFF) << 16) + \
                                   ((header[6] & 0xFF) << 8)  + \
                                   ((header[7] & 0xFF) << 0)

    gtp_dict['payload'] = message[8:]
    return gtp_dict



def testGTP(p="test", r=True):
    t = createTEID(r)
    h, p, m = encapsulate(p, t)
    return decapsulate(m)
