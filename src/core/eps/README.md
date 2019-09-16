## Description of the OpenFlow Interface

The OpenFlow Messages for the Metering Table are the following:
```
void OFInterface::install_default_meter_drop(fluid_base::OFConnection* of_conn, uint32_t meter_id)
void OFInterface::install_default_meter_dscp(fluid_base::OFConnection* of_conn, uint32_t meter_id)
void OFInterface::install_meter_mod(fluid_base::OFConnection* of_conn, uint16_t flags, uint32_t meter_id, uint16_t type, uint32_t rate, uint32_t burst_size, uint8_t prec_level, uint32_t experimenter)
void OFInterface::modify_meter_mod(fluid_base::OFConnection* of_conn, uint32_t meter_id, uint32_t rate, uint32_t burst_size)


void OFInterface::install_default_meter_UE_ul_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, uint64_t ul_tunnel, Metadata metadata)
void OFInterface::install_default_meter_UE_dl_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, const std::string UE_ip, const uint64_t dl_tunnel, const std::string ENB_ip, Metadata metadata)

void redirect_edge_service_dl_meter_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, const std::string UE_ip, const uint64_t dl_tunnel, const std::string ENB_ip, std::string from, std::string to, Metadata metadata)
void redirect_edge_service_ul_meter_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, uint64_t ul_tunnel, std::string from, std::string to, Metadata metadata)


void OFInterface::get_meter_stats(fluid_base::OFConnection* of_conn)
void OFInterface::get_meter_features_stats(fluid_base::OFConnection* of_conn)
void OFInterface::get_meter_config_stats(fluid_base::OFConnection* of_conn, uint32_t meter_id)
void OFInterface::flush_meter(fluid_base::OFConnection* of_conn, uint32_t meter_id)

```
 - install_default_meter_drop 		- is installing the MeterTable number 1 with a rate of 1GBps and burst rate of 50MBs.
 - install_default_meter_dscp 		- is installing the MeterTable number 1 with a rate of 1GBps , burst rate of 50MBs and level of precentage of 20%.
 - install_meter_mod 	      		- is installing the MeterTable number [2 - 4294901760] with dynamic rate , burst rate and level of precentage.
 - modify_meter_mod	      		- is modifing a MeterTable.
 - install_default_meter_UE_ul_flow 	- is installing the upling flow using and map a meter to the action field.
 - install_default_meter_UE_dl_flow	- is installing the downlink flow using and map a meter to the action field.
 - redirect_edge_service_dl_meter_flow  - is installing an redirect downlink flow using and map a meter to the action field.
 - redirect_edge_service_ul_meter_flow  - is installing an redirect uplink flow using and map a meter to the action field.
 - get_meter_stats 			- gathering all the stats of all the meters.
 - get_meter_features_stats		- gathering all the stats of the features of all the meters.
 - get_meter_config_stats		- gathering all the stats of the configuration of all the meters.
 - flush_meter				- it delets a specific MeterTable.


