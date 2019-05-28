/*
 * Copyright 2016-2018 Eurecom and Mosaic5G Platforms Authors
 * Licensed to the Mosaic5G under one or more contributor license
 * agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership.
 * The Mosaic5G licenses this file to You under the
 * Apache License, Version 2.0  (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the Mosaic5G:
 *  	contact@mosaic5g.io
 */

/*!
  \file
  \brief
  \author
  \company
  \email:
*/

#ifndef __OF_INTERFACE_H__
#define __OF_INTERFACE_H__

#include <fluid/OFServer.hh>
#include <fluid/of10msg.hh>
#include <fluid/of13msg.hh>

#include "metadata.h"

//LL-MEC OpenFlow interface
namespace llmec {
namespace core {
namespace eps {

class OFInterface {
  public:
    void install_flow_mod(fluid_msg::of10::PacketIn &pi, fluid_base::OFConnection* of_conn, uint64_t src, uint64_t dst, uint16_t out_port);
    void install_flow_mod(fluid_msg::of13::PacketIn &pi, fluid_base::OFConnection* of_conn, uint64_t src, uint64_t dst, uint16_t out_port);
    void install_default_meter_drop(fluid_base::OFConnection* of_conn, uint32_t meter_id);
    void install_default_meter_dscp(fluid_base::OFConnection* of_conn, uint32_t meter_id);
/*
 * MeteringTable
 * ##################################################################
 * install_meter_mod_drop - installing the metering table rules
 * install_default_meter_UE_ul_flow - defining the ul flow using the metering in the definition
 * install_default_meter_UE_dl_flow - defining the dl flow using the metering in the definition
 */
    void install_meter_mod(fluid_base::OFConnection* of_conn, uint16_t flags, uint32_t meter_id, uint16_t type, uint32_t rate, uint32_t burst_size, uint8_t prec_level, uint32_t experimenter);
    void modify_meter_mod_drop(fluid_base::OFConnection* of_conn, uint32_t meter_id, uint32_t rate, uint32_t burst_size);
    void modify_meter_mod_dscp(fluid_base::OFConnection* of_conn, uint32_t meter_id, uint32_t rate, uint32_t burst_size, uint8_t prec_level);
    void install_default_meter_UE_ul_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, uint64_t ul_tunnel, Metadata metadata);
    void install_default_meter_UE_dl_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, const std::string UE_ip, const uint64_t dl_tunnel, const std::string ENB_ip, Metadata metadata);
/*
 * ##################################################################
 */
    void install_default_flow(fluid_base::OFConnection* of_conn);
    void install_default_UE_ul_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint64_t ul_tunnel_id, Metadata metadata);
    void install_default_UE_dl_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, std::string UE_ip, uint64_t dl_tunnel_id, std::string ENB_ip, Metadata Metadata);
    void redirect_edge_service_ul_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint64_t ul_tunnel_id, std::string from, std::string to, Metadata metadata);
    void redirect_edge_service_dl_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, std::string UE_ip, uint64_t dl_tunnel_id, std::string ENB_ip, std::string from, std::string to, Metadata metadata);
    void get_flow_stats(fluid_base::OFConnection* of_conn, uint32_t xid, uint8_t table_id, uint64_t cookie, uint64_t cookie_mask);

/*
 * MeteringTable
 * ##################################################################
 * redirect_edge_service_dl_meter_flow - defining the downlink flow redirect using an meterTable
 * redirect_edge_service_ul_meter_flow - defining the uplink flow redirect using an meterTable
 */
    void redirect_edge_service_dl_meter_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, const std::string UE_ip, const uint64_t dl_tunnel, const std::string ENB_ip, std::string from, std::string to, Metadata metadata);
    void redirect_edge_service_ul_meter_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, uint64_t ul_tunnel, std::string from, std::string to, Metadata metadata);
/*
 * MeteringTable
 * ##################################################################
 * get_meter_stats - gets the informations regarding the meters
 * get_meter_features_stats - gets the informations regarding the meters features
 */
    void get_meter_stats(fluid_base::OFConnection* of_conn);
    void get_meter_features_stats(fluid_base::OFConnection* of_conn);
    void get_meter_config_stats(fluid_base::OFConnection* of_conn, uint32_t meter_id);
/*
 * ##################################################################
 */
    void flush_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id);
/*
 * MeteringTable
 * ##################################################################
 * flush_meter - deletes the meters
 */
    void flush_meter(fluid_base::OFConnection* of_conn, uint32_t meter_id);
/*
 * ##################################################################
 */
};

} // namespace eps
} // namespace core
} // namespace llmec
#endif
