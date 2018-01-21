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
