Low Latency MEC platform (LL-MEC)
======================================
## What is LL-MEC?
LL-MEC is a real-time Multi-access Edge Computing platform.
* The bulk of the code is written from scratch using C++ and currently supports x64 Linux systems.
* The implementation aims to support core network programmability coordinated with RAN real-time operation and provide flexible application programming environment at the network edge.
* LL-MEC is well suited to conduct proof-of-concept experiments.
* LL-MEC is designed to easily expand the control function as well as the supported OpenFlow rules.

## Library dependency
* libfluid (http://opennetworkingfoundation.github.io/libfluid/): libfluid is a library bundle that provides the basic features to implement an OpenFlow controller
* nlohmann/json (https://github.com/nlohmann/json): craft and parse JSON message
* Pistache (https://github.com/oktal/pistache): REST API framework
* spdlog (https://github.com/gabime/spdlog): logging

## Dependencies installation
    $ ./install_dependencies.sh

## Building instruction
#### Prerequisite
* CMake version 2.8 or newer
* GCC version 4.8.1 or newer (for c++11 support)

#### To build
    ./build_ll-mec.sh
    # the executable will be present in the same folder
    
    ./clean_ll-mec.sh
    # to clean

## Configuration example (llmec_config.json)
    {
      "llmec": {
        "address": "0.0.0.0",
        "port": 6653,
        "number_of_workers": 4,
        "secure_connection": false
      },
      "northbound_api": {
        "port": 9999
      },
      "gateway": {
        "mac": "00:24:9b:23:33:a6"
      },
      "ovs_switch": {
        "s1u_port": 2,
        "external_port": 1
      }
    }

## Usage example
    $ sudo ./ll-mec -h
    [2018-01-21 23:16:08] [info] Low Latency MEC platform
    [2018-01-21 23:16:08] [info] -h
    [2018-01-21 23:16:08] [info] 
    [2018-01-21 23:16:08] [info] 	This help
    [2018-01-21 23:16:08] [info] 
    [2018-01-21 23:16:08] [info] -c [CONFIG_PATH]
    [2018-01-21 23:16:08] [info] 
    [2018-01-21 23:16:08] [info] 	Load config file from [CONFIG_PATH]. Default config will loaded if not specified

    $ sudo ./ll-mec
    [2018-01-21 23:14:56] [info] Stats manager started
    [2018-01-21 23:14:56] [info] Server running (0.0.0.0:6653)
    [2018-01-21 23:15:00] [info] Switch id=0 started
    [2018-01-21 23:15:00] [info] Switch id=0 established
    [2018-01-21 23:15:00] [info] Switch id=0 installed default flow
    [2018-01-21 23:15:13] [info] Add UE: {"enb_ip":"192.168.0.3","imsi":"123456789012345","s1_dl_teid":4,"s1_ul_teid":3,"ue_id":1,"ue_ip":"172.16.0.2"}
    [2018-01-21 23:15:25] [info] Redirected UE id=1 from 192.168.12.3 to 192.168.12.1
    [2018-01-21 23:15:33] [info] No redirected traffic for UE id=1

## Contact
Please email to Mosaic5G (mosaic5g@lists.eurecom.fr)

## Description of the ll-mec

This version of the ll-mec it contains a set of metering table enabled in the OF13 messages


## The software architecture 

![Imgur](https://i.imgur.com/gQUrgU3.jpg)

## Installation

In order to install the ll-mec using the Ubuntu CLI

```
pou@ubuntu:~/Desktop/Mp2-BwManagementApi/ll-mec$ ./build_ll-mec.sh
```

To run the ll-mec service on the working directory there is a script ll-mec.sh
```
pou@ubuntu:~/Desktop/Mp2-BwManagementApi/ll-mec$ sudo ./ll-mec
```

## Description of the meterID implementation
```

meterID = function(eps_bearer_id, imsi, s1_teid_ul/s1_teid_dl);

if(sliceID=0){
	meterID is assigned per user
}
else if(sliceID>0 && sliceID<=16){
	meterID is assigned for each sliceID
	meterID = sliceID;
}
```

## OpenvSwitch CLI commands
```
  595  sudo ovs-ofctl dump-flows edge
  596  sudo ovs-ofctl -O OpenFlow13 add-meter edge meter=0,kbps,band=type=drop,rate=50000
  597  sudo ovs-ofctl -O OpenFlow13 add-meter edge meter=1,kbps,band=type=drop,rate=50000
  600  sudo ovs-ofctl -O OpenFlow13 dump-meters edge
  601  sudo ovs-ofctl -O OpenFlow13 dump-flows edge
  604  sudo ovs-ofctl -O OpenFlow13 mod-meter edge meter=2,kbps,band=type=drop,rate=5000
  605  sudo ovs-ofctl -O OpenFlow13 add-meter edge meter=2,kbps,band=type=drop,rate=5000
  606  sudo ovs-ofctl -O OpenFlow13 --timestamp add-meter edge meter=2,kbps,burst,band=type=drop,rate=3000,burst_size=300000
  607  sudo ovs-ofctl -O OpenFlow13 --timestamp add-meter edge meter=3,kbps,burst,band=type=drop,rate=3000,burst_size=300000
  608  sudo ovs-ofctl -O OpenFlow13 dump-meters edge
  609  sudo ovs-ofctl add-flow edge in_port=11,dl_dst=22:00:00:00:00:00,dl_src=22:11:11:11:11:11,dl_type=0x0800,actions=meter:2,output:13
  610  sudo ovs-ofctl -O OpenFlow13 add-flow edge in_port=11,dl_dst=22:00:00:00:00:00,dl_src=22:11:11:11:11:11,dl_type=0x0800,actions=meter:2,output:13
  611  sudo ovs-ofctl dump-flows edge
  612  sudo ovs-ofctl dump-tables edge
  613  sudo ovs-ofctl dump-table-features edge
  614  sudo ovs-ofctl -O OpenFlow13 dump-table-features edge
  617  sudo ovs-ofctl -O OpenFlow13 --timestamp add-meter edge meter=3,kbps,burst,band=type=drop,rate=30000,burst_size=5000
  618  sudo ovs-ofctl -O OpenFlow13 --timestamp add-meter edge meter=3,kbps,burst,band=type=drop,rate=3000,burst_size=300000
  619  sudo ovs-ofctl -O OpenFlow13 add-meter edge meter=3,kbps,burst,band=type=drop,rate=3000,burst_size=300000
  621  sudo ovs-ofctl -O OpenFlow13 add-meter edge meter=2,kbps,band=type=drop,rate=5000
  622  sudo ovs-ofctll -O OpenFlow13 dump-mets edge
  623  sudo ovs-ofctl -O OpenFlow13 dump-mets edge
  624  sudo ovs-ofctl -O OpenFlow13 dump-meters edge
  625  sudo ovs-ofctl -O OpenFlow13 add-meter edge meter=2,kbps,band=type=drop,rate=5000
  626  sudo ovs-ofctl -O OpenFlow13 add-meter edge meter=2,kbps,band=type=drop,rate=50000
  627  sudo ovs-ofctl -O OpenFlow13 add-meter edge meter=12,kbps,band=type=drop,rate=50000
  632  sudo ovs-ofctl -O OpenFlow13 add-meter edge meter=12,kbps,band=type=drop,rate=50000
  633  sudo ovs-ofctl -O OpenFlow13 --timestamp add-meter edge meter=3,kbps,burst,band=type=drop,rate=30000,burst_size=5000
  639  sudo ovs-ofctl -O OpenFlow13 --timestamp add-meter edge meter=3,kbps,burst,band=type=drop,rate=30000,burst_size=5000
```


