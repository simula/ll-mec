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
      "gateway": {
        "mac": "00:24:9b:23:33:a6"
      },
      "ovs_switch": {
        "s1u_port": 2,
        "external_port": 1
      }
    }

## Usage example
    $ sudo ./ll-mec
    Server running (0.0.0.0:6653)
    Connection id=0 started
    Connection id=0 established

## Contact
Please email to Mosaic5G (mosaic5g@lists.eurecom.fr)
