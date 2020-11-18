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
  \author Anta Huang, N. Nikaein, Mihai IDU
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr, idumihai16@gmail.com
*/


#include "of_interface.h"
#include "conf.h"

namespace llmec {
namespace core {
namespace eps {

//TODO OpenFlow message field wrapper specifically for LL-MEC
/*
 * This is done for OpenFlow10
 */
void OFInterface::install_flow_mod(fluid_msg::of10::PacketIn &pi, fluid_base::OFConnection* ofconn,
    uint64_t src, uint64_t dst, uint16_t out_port) {
  // Flow mod message
  uint8_t* buffer;
  /* Messages constructors allow to add all
     values in a row. The fields order follows
     the specification */
  fluid_msg::of10::FlowMod fm(pi.xid(),  //xid
      123, // cookie
      fluid_msg::of10::OFPFC_ADD, // command
      5, // idle timeout
      10, // hard timeout
      100, // priority
      pi.buffer_id(), //buffer id
      0, // outport
      0); // flags
  fluid_msg::of10::Match m;
  m.dl_src(((uint8_t*) &src) + 2);
  m.dl_dst(((uint8_t*) &dst) + 2);
  fm.match(m);
  fluid_msg::of10::OutputAction act(out_port, 1024);
  fm.add_action(act);
  buffer = fm.pack();
  ofconn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

/*
 * This is done for OpenFlow13. Up is installing the flow mod for OpenFlow10. Below for OpenFlow13
 */
void OFInterface::install_flow_mod(fluid_msg::of13::PacketIn &pi, fluid_base::OFConnection* ofconn,
    uint64_t src, uint64_t dst, uint16_t out_port) {
  // Flow mod message
  uint8_t* buffer;
  /*You can also set the message field using
    class methods which have the same names from
    the field present on the specification*/
  fluid_msg::of13::FlowMod fm;
  fm.xid(pi.xid());
  fm.cookie(123);
  fm.cookie_mask(0xffffffffffffffff);
  fm.table_id(0);
  fm.command(fluid_msg::of13::OFPFC_ADD);
  fm.idle_timeout(5);
  fm.hard_timeout(10);
  fm.priority(100);
  fm.buffer_id(pi.buffer_id());
  fm.out_port(0);
  fm.out_group(0);
  fm.flags(0);
  fluid_msg::of13::EthSrc fsrc(((uint8_t*) &src) + 2);
  fluid_msg::of13::EthDst fdst(((uint8_t*) &dst) + 2);
  fm.add_oxm_field(fsrc);
  fm.add_oxm_field(fdst);
  fluid_msg::of13::OutputAction act(out_port, 1024);
  fluid_msg::of13::ApplyActions inst;
  inst.add_action(act);
  fm.add_instruction(inst);
  buffer = fm.pack();
  ofconn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
  fluid_msg::of13::Match m;
  fluid_msg::of13::MultipartRequestFlow rf(2, 0x0, 0, fluid_msg::of13::OFPP_ANY, fluid_msg::of13::OFPG_ANY,
      0x0, 0x0, m);
  buffer = rf.pack();
  ofconn->send(buffer, rf.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}


/*
 * Default Install Flow Mod
 */
void OFInterface::install_default_flow(fluid_base::OFConnection* of_conn) {
  uint8_t* buffer;
  fluid_msg::of13::FlowMod fm(42, 0, 0xffffffffffffffff, 0, fluid_msg::of13::OFPFC_ADD, 0, 0, 0,
      0xffffffff, 0, 0, 0);
  fluid_msg::of13::OutputAction *act = new fluid_msg::of13::OutputAction(fluid_msg::of13::OFPP_NORMAL,
      fluid_msg::of13::OFPCML_NO_BUFFER);
  fluid_msg::of13::ApplyActions *inst = new fluid_msg::of13::ApplyActions();
  inst->add_action(act);
  fm.add_instruction(inst);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}


/*
 * Default Install Meter Mod
*/

void OFInterface::install_default_meter_drop(fluid_base::OFConnection* of_conn, uint32_t meter_id) {
  uint8_t* buffer;
  fluid_msg::of13::MeterMod mm(42, fluid_msg::of13::OFPMC_ADD, fluid_msg::of13::OFPMF_KBPS, meter_id);
  fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBandDrop(1000000, 50000);
  mm.add_band(mb1);
  buffer = mm.pack();
  of_conn->send(buffer, mm.length());
  fluid_msg::OFMsg::free_buffer(buffer);

}

void OFInterface::install_default_meter_dscp(fluid_base::OFConnection* of_conn, uint32_t meter_id) {
  uint8_t* buffer;
//  fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBand(uint16_t type, uint32_t rate, uint32_t burst_size);
//fluid_msg::of13::OFPMBT_DROP         - 0x0001
//fluid_msg::of13::OFPMBT_DSCP_REMARK  - 0x0002
//fluid_msg::of13::OFPMBT_EXPERIMENTER - 0xFFFF of13::OFPMBT_EXPERIMENTER
//Example: sudo ovs-ofctl -O OpenFlow13 add-meter edge meter=6,kbps,burst,band=type=dscp_remark,rate=30000,prec_level=14,burst_size=30000
//fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBand(uint16_t type, uint32_t rate, uint32_t burst_size, uint8_t prec_level)
//  fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBandDSCPRemark(777, 888);
//MeterBandExperimenter
//fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBand(uint16_t type, uint32_t rate, uint32_t burst_size);

//  fluid_msg::of13::MeterMod mm;
//  mm.xid(42);
//  mm.command(fluid_msg::of13::OFPMC_ADD);
//fluid_msg::of13::OFPMF_KBPS
//fluid_msg::of13::OFPMF_BURST
//  mm.flags(fluid_msg::of13::OFPMF_KBPS);
//  mm.flags(fluid_msg::of13::OFPMF_BURST);
//  mm.meter_id(10);
//  fluid_msg::of13::MeterMod *mm = new fluid_msg::of13::MeterMod(42, fluid_msg::of13::OFPMC_ADD, fluid_msg::of13::OFPMF_KBPS, 1, fluid_msg::of13::MeterBandList& mb);
  fluid_msg::of13::MeterMod mm(42, fluid_msg::of13::OFPMC_ADD, fluid_msg::of13::OFPMF_KBPS, meter_id);
  fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBandDSCPRemark(1000000, 50000, 50);
  mm.add_band(mb1);
  buffer = mm.pack();
  of_conn->send(buffer, mm.length());
  fluid_msg::OFMsg::free_buffer(buffer);

}
/*
 * Add  a  meter  entry to switch's tables. The meter
 * syntax is described in section Meter Syntax, below.
 * This OpenFlow13 Message it can be transformed into CLI command as below:
 * sudo ovs-ofctl -O OpenFlow13 mod-meter edge meter=uint32_t meter_id,kbps,band=type=drop,rate= uint32_t rate
 */

void OFInterface::install_meter_mod(fluid_base::OFConnection* of_conn, uint16_t flags, uint32_t meter_id, uint16_t type, uint32_t rate, uint32_t burst_size, uint8_t prec_level, uint32_t experimenter) {
/* Meter mod message */
  uint8_t* buffer;
  /* Meter Band header
	type can be OFPMBT_DROP, OFPMBT_DSCP_REMARK or OFPMBT_EXPERIMENTER
  fluid_msg::of13::MeterMod mm(43, fluid_msg::of13::OFPMC_ADD, flags, meter_id); - to ADD a meter
  fluid_msg::of13::MeterMod mm(43, fluid_msg::of13::OFPMC_MODIFY, flags, meter_id); - to MODIFY a meter
  fluid_msg::of13::MeterMod mm(43, fluid_msg::of13::OFPMC_DELETE, flags, meter_id); - to DELETE a meter
  */
  fluid_msg::of13::MeterMod mm(43, fluid_msg::of13::OFPMC_ADD, flags, meter_id);
//  fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBandDrop(rate, burst_size);
  fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBandDrop(rate, burst_size);
  //mm.command(fluid_msg::of13::OFPMC_ADD);
	/*
         * kbps__0x0001
         * pkps__0x0002
         * burst_0x0004
         * stats_0x0008
         *
         */
//  mm.flags(fluid_msg::of13::OFPMF_KBPS);
	/*
	 * General_meter_id__0x00000000-0xFFFF0000
	 * Slow_datapath_____0xFFFFFFFD
	 * Controller________0xFFFFFFFE
	 * All_______________0xFFFFFFFF
	 *
	 */
  mm.add_band(mb1);
  buffer = mm.pack();
  of_conn->send(buffer, mm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

void OFInterface::modify_meter_mod_drop(fluid_base::OFConnection* of_conn, uint32_t meter_id, uint32_t rate, uint32_t burst_size) {
/* Meter mod message */
  uint8_t* buffer;
  /* Meter Band header
	type can be OFPMBT_DROP, OFPMBT_DSCP_REMARK or OFPMBT_EXPERIMENTER
  fluid_msg::of13::MeterMod mm(43, fluid_msg::of13::OFPMC_ADD, flags, meter_id); - to ADD a meter
  fluid_msg::of13::MeterMod mm(43, fluid_msg::of13::OFPMC_MODIFY, flags, meter_id); - to MODIFY a meter
  fluid_msg::of13::MeterMod mm(43, fluid_msg::of13::OFPMC_DELETE, flags, meter_id); - to DELETE a meter
  */
  fluid_msg::of13::MeterMod mm(43, fluid_msg::of13::OFPMC_MODIFY, fluid_msg::of13::OFPMF_KBPS, meter_id);
  fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBandDrop(rate, burst_size);
  //mm.command(fluid_msg::of13::OFPMC_ADD);
	/*
         * kbps__0x0001
         * pkps__0x0002
         * burst_0x0004
         * stats_0x0008
         *
         */
//  mm.flags(fluid_msg::of13::OFPMF_KBPS);
	/*
	 * General_meter_id__0x00000000-0xFFFF0000
	 * Slow_datapath_____0xFFFFFFFD
	 * Controller________0xFFFFFFFE
	 * All_______________0xFFFFFFFF
	 *
	 */
  mm.add_band(mb1);
  buffer = mm.pack();
  of_conn->send(buffer, mm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

void OFInterface::install_meter_mod_drop(fluid_base::OFConnection* of_conn, uint32_t meter_id, uint32_t rate, uint32_t burst_size) {
  uint8_t* buffer;
  fluid_msg::of13::MeterMod mm(42, fluid_msg::of13::OFPMC_ADD, fluid_msg::of13::OFPMF_KBPS, meter_id);
  fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBandDrop(rate, burst_size);
  mm.add_band(mb1);
  buffer = mm.pack();
  of_conn->send(buffer, mm.length());
  fluid_msg::OFMsg::free_buffer(buffer);

}

void OFInterface::modify_meter_mod_dscp(fluid_base::OFConnection* of_conn, uint32_t meter_id, uint32_t rate, uint32_t burst_size, uint8_t prec_level) {
/* Meter mod message */
  uint8_t* buffer;
  fluid_msg::of13::MeterMod mm(43, fluid_msg::of13::OFPMC_MODIFY, fluid_msg::of13::OFPMF_KBPS, meter_id);
  fluid_msg::of13::MeterBand *mb1 = new fluid_msg::of13::MeterBandDSCPRemark(rate, burst_size, prec_level);
  mm.add_band(mb1);
  buffer = mm.pack();
  of_conn->send(buffer, mm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}
/*
 * InstallDefaultMeterUEUplingFlow
 * This OpenFlow13 Message it can be transformed into CLI command as below:
 * sudo ovs-ofctl add-flow -O OpenFlow13 edge in_port=11,ul_dst=22:00:00:00:00:00,ul_src=22:11:11:11:11:11,ul_type=0x0800,actions=meter:12,output:13
 */

void OFInterface::install_default_meter_UE_ul_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, uint64_t ul_tunnel, Metadata metadata) {
  Conf* llmec_config = Conf::getInstance();
  uint8_t* buffer;
  fluid_msg::of13::Match m;
  fluid_msg::of13::InPort in_port(llmec_config->X["ovs_switch"]["s1u_port"].get<int>());
  fluid_msg::of13::TUNNELId ul_tunnel_id(ul_tunnel);
  /* IPv4 packet, Not intend to deal with the field dependency */
  fluid_msg::of13::EthType eth_type(0x0800);
  m.add_oxm_field(eth_type);
  m.add_oxm_field(in_port);
  m.add_oxm_field(ul_tunnel_id);

  fluid_msg::of13::FlowMod fm;
  fm.xid(43);
  fm.cookie(flow_id);
  fm.cookie_mask(0xffffffffffffffff);
  fm.table_id(0);
  fm.command(fluid_msg::of13::OFPFC_ADD);
  fm.idle_timeout(0);
  fm.hard_timeout(0);
  fm.priority(1);
  fm.buffer_id(0xffffffff);
  fm.out_port(1);
  fm.out_group(0);
  fm.flags(0);
  fm.match(m);

  auto out = fluid_msg::EthAddress(llmec_config->X["gateway"]["mac"].get<std::string>());
  fluid_msg::of13::ApplyActions act;
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::EthDst(out)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPDSCP(metadata.ipdscp)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPECN(metadata.ipecn)));
  act.add_action(new fluid_msg::of13::OutputAction(llmec_config->X["ovs_switch"]["external_port"].get<int>(), 1024));
//  fluid_msg::of13::Meter meter;
//  meter.meter_id;
//  fm.add_instruction(act);
  fm.add_instruction(new fluid_msg::of13::Meter(meter_id));
  fm.add_instruction(act);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

/*
 * InstallDefaultMeterUEDownlinkFlow
 * This OpenFlow13Message it can be transformed into CLI commands as below
 * sudo ovs-ofctl add-flow -O OpenFlow13 edge in_port=11,dl_dst=22:00:00:00:00:00,dl_src=22:11:11:11:11:11,dl_type=0x0800,actions=meter:12,output:13
 */
void OFInterface::install_default_meter_UE_dl_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, const std::string UE_ip, const uint64_t dl_tunnel, const std::string ENB_ip, Metadata metadata) {
  Conf* llmec_config = Conf::getInstance();
  uint8_t* buffer;
  fluid_msg::of13::Match m;
  // By default, allow IP traffic
  fluid_msg::of13::EthType eth_type(0x0800);
  fluid_msg::IPAddress ue_ip_addr(UE_ip);
  fluid_msg::of13::IPv4Dst ip_dst(ue_ip_addr);
  m.add_oxm_field(eth_type);
  m.add_oxm_field(ip_dst);

  // Default value for fields below
  fluid_msg::of13::FlowMod fm;
  fm.xid(43);
  fm.cookie(flow_id);
  fm.cookie_mask(0xffffffffffffffff);
  fm.table_id(0);
  fm.command(fluid_msg::of13::OFPFC_ADD);
  fm.idle_timeout(0);
  fm.hard_timeout(0);
  fm.priority(1);
  fm.buffer_id(0xffffffff);
  fm.out_port(1);
  fm.out_group(0);
  fm.flags(0);
  fm.match(m);

  auto out = fluid_msg::EthAddress(llmec_config->X["gateway"]["mac"].get<std::string>());
  fluid_msg::of13::ApplyActions act;
  fluid_msg::of13::TUNNELId dl_tunnel_id(dl_tunnel);
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::TUNNELId(dl_tunnel_id)));
  fluid_msg::IPAddress enb_ip_addr(ENB_ip);
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::TUNNELDst(enb_ip_addr)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPDSCP(metadata.ipdscp)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPECN(metadata.ipecn)));
  act.add_action(new fluid_msg::of13::OutputAction(llmec_config->X["ovs_switch"]["s1u_port"].get<int>(), 1024));
//  fluid_msg::of13::Meter meter;
//  meter.meter_id;
  fm.add_instruction(act);
  fm.add_instruction(new fluid_msg::of13::Meter(meter_id));
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

/*
 *
 */

void OFInterface::install_default_UE_ul_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint64_t ul_tunnel, Metadata metadata) {
  Conf* llmec_config = Conf::getInstance();
  uint8_t* buffer;
  fluid_msg::of13::Match m;
  fluid_msg::of13::InPort in_port(llmec_config->X["ovs_switch"]["s1u_port"].get<int>());
  fluid_msg::of13::TUNNELId ul_tunnel_id(ul_tunnel);
  /* IPv4 packet, Not intend to deal with the field dependency */
  fluid_msg::of13::EthType eth_type(0x0800);
  m.add_oxm_field(eth_type);
  m.add_oxm_field(in_port);
  m.add_oxm_field(ul_tunnel_id);

  fluid_msg::of13::FlowMod fm;
  fm.xid(43);
  fm.cookie(flow_id);
  fm.cookie_mask(0xffffffffffffffff);
  fm.table_id(0);
  fm.command(fluid_msg::of13::OFPFC_ADD);
  fm.idle_timeout(0);
  fm.hard_timeout(0);
  fm.priority(1);
  fm.buffer_id(0xffffffff);
  fm.out_port(1);
  fm.out_group(0);
  fm.flags(0);
  fm.match(m);

  auto out = fluid_msg::EthAddress(llmec_config->X["gateway"]["mac"].get<std::string>());
  fluid_msg::of13::ApplyActions act;
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::EthDst(out)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPDSCP(metadata.ipdscp)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPECN(metadata.ipecn)));
  act.add_action(new fluid_msg::of13::OutputAction(llmec_config->X["ovs_switch"]["external_port"].get<int>(), 1024));
  fm.add_instruction(act);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

void OFInterface::install_default_UE_dl_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, const std::string UE_ip, const uint64_t dl_tunnel, const std::string ENB_ip, Metadata metadata) {
  Conf* llmec_config = Conf::getInstance();
  uint8_t* buffer;
  fluid_msg::of13::Match m;
  // By default, allow IP traffic
  fluid_msg::of13::EthType eth_type(0x0800);
  fluid_msg::IPAddress ue_ip_addr(UE_ip);
  fluid_msg::of13::IPv4Dst ip_dst(ue_ip_addr);
  m.add_oxm_field(eth_type);
  m.add_oxm_field(ip_dst);

  // Default value for fields below
  fluid_msg::of13::FlowMod fm;
  fm.xid(43);
  fm.cookie(flow_id);
  fm.cookie_mask(0xffffffffffffffff);
  fm.table_id(0);
  fm.command(fluid_msg::of13::OFPFC_ADD);
  fm.idle_timeout(0);
  fm.hard_timeout(0);
  fm.priority(1);
  fm.buffer_id(0xffffffff);
  fm.out_port(1);
  fm.out_group(0);
  fm.flags(0);
  fm.match(m);

  auto out = fluid_msg::EthAddress(llmec_config->X["gateway"]["mac"].get<std::string>());
  fluid_msg::of13::ApplyActions act;
  fluid_msg::of13::TUNNELId dl_tunnel_id(dl_tunnel);
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::TUNNELId(dl_tunnel_id)));
  fluid_msg::IPAddress enb_ip_addr(ENB_ip);
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::TUNNELDst(enb_ip_addr)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPDSCP(metadata.ipdscp)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPECN(metadata.ipecn)));
  act.add_action(new fluid_msg::of13::OutputAction(llmec_config->X["ovs_switch"]["s1u_port"].get<int>(), 1024));
  fm.add_instruction(act);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

void OFInterface::redirect_edge_service_ul_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint64_t ul_tunnel, std::string from, std::string to, Metadata metadata) {
  Conf* llmec_config = Conf::getInstance();
  uint8_t* buffer;
  fluid_msg::of13::Match m;
  fluid_msg::of13::InPort in_port(llmec_config->X["ovs_switch"]["s1u_port"].get<int>());
  fluid_msg::of13::EthType eth_type(0x0800);
  fluid_msg::of13::TUNNELId ul_tunnel_id(ul_tunnel);
  fluid_msg::of13::IPv4Dst ip_dst(from);
  m.add_oxm_field(in_port);
  m.add_oxm_field(ul_tunnel_id);
  m.add_oxm_field(eth_type);
  m.add_oxm_field(ip_dst);

  fluid_msg::of13::FlowMod fm;
  fm.xid(43);
  fm.cookie(flow_id);
  fm.cookie_mask(0xffffffffffffffff);
  fm.table_id(0);
  fm.command(fluid_msg::of13::OFPFC_ADD);
  fm.idle_timeout(0);
  fm.hard_timeout(0);
  fm.priority(2);
  fm.buffer_id(0xffffffff);
  fm.out_port(1);
  fm.out_group(0);
  fm.flags(0);
  fm.match(m);


  auto out = fluid_msg::EthAddress(llmec_config->X["gateway"]["mac"].get<std::string>());
  fluid_msg::of13::ApplyActions act;
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::EthDst(out)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPv4Dst(to)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPDSCP(metadata.ipdscp)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPECN(metadata.ipecn)));
  act.add_action(new fluid_msg::of13::OutputAction(llmec_config->X["ovs_switch"]["external_port"].get<int>(), 1024));
  fm.add_instruction(act);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

void OFInterface::redirect_edge_service_dl_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, const std::string UE_ip, const uint64_t dl_tunnel, const std::string ENB_ip, std::string from, std::string to, Metadata metadata) {
  Conf* llmec_config = Conf::getInstance();
  uint8_t* buffer;
  fluid_msg::of13::Match m;
  // By default, allow IP traffic
  fluid_msg::of13::EthType eth_type(0x0800);
  fluid_msg::IPAddress ue_ip_addr(UE_ip);
  fluid_msg::of13::IPv4Dst ip_dst(ue_ip_addr);
  fluid_msg::of13::IPv4Src ip_src(to);
  m.add_oxm_field(eth_type);
  m.add_oxm_field(ip_dst);
  m.add_oxm_field(ip_src);

  // Default value for fields below
  fluid_msg::of13::FlowMod fm;
  fm.xid(43);
  fm.cookie(flow_id);
  fm.cookie_mask(0xffffffffffffffff);
  fm.table_id(0);
  fm.command(fluid_msg::of13::OFPFC_ADD);
  fm.idle_timeout(0);
  fm.hard_timeout(0);
  fm.priority(2);
  fm.buffer_id(0xffffffff);
  fm.out_port(1);
  fm.out_group(0);
  fm.flags(0);
  fm.match(m);

  auto out = fluid_msg::EthAddress(llmec_config->X["gateway"]["mac"].get<std::string>());
  fluid_msg::of13::ApplyActions act;
  fluid_msg::of13::TUNNELId dl_tunnel_id(dl_tunnel);
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::TUNNELId(dl_tunnel_id)));
  act.add_action(new fluid_msg::of13::OutputAction(llmec_config->X["ovs_switch"]["s1u_port"].get<int>(), 1024));
  fm.add_instruction(act);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  act.add_action(new fluid_msg::of13::OutputAction(llmec_config->X["ovs_switch"]["s1u_port"].get<int>(), 1024));
  fm.add_instruction(act);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}


void OFInterface::get_flow_stats(fluid_base::OFConnection* of_conn, uint32_t xid, uint8_t table_id, uint64_t cookie, uint64_t cookie_mask) {
  uint8_t* buffer;
  fluid_msg::of13::MultipartRequestFlow mrf(xid, 0, fluid_msg::of13::OFPTT_ALL, fluid_msg::of13::OFPP_ANY, fluid_msg::of13::OFPG_ANY, cookie, cookie_mask);
  buffer = mrf.pack();
  of_conn->send(buffer, mrf.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

/*
 * The flow redirection using a meterTable
 *
 */
 void OFInterface::redirect_edge_service_ul_meter_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, uint64_t ul_tunnel, std::string from, std::string to, Metadata metadata) {
   Conf* llmec_config = Conf::getInstance();
   uint8_t* buffer;
   fluid_msg::of13::Match m;
   fluid_msg::of13::InPort in_port(llmec_config->X["ovs_switch"]["s1u_port"].get<int>());
   fluid_msg::of13::EthType eth_type(0x0800);
   fluid_msg::of13::TUNNELId ul_tunnel_id(ul_tunnel);
   fluid_msg::of13::IPv4Dst ip_dst(from);
   m.add_oxm_field(in_port);
   m.add_oxm_field(ul_tunnel_id);
   m.add_oxm_field(eth_type);
   m.add_oxm_field(ip_dst);

   fluid_msg::of13::FlowMod fm;
   fm.xid(43);
   fm.cookie(flow_id);
   fm.cookie_mask(0xffffffffffffffff);
   fm.table_id(0);
   fm.command(fluid_msg::of13::OFPFC_ADD);
   fm.idle_timeout(0);
   fm.hard_timeout(0);
   fm.priority(2);
   fm.buffer_id(0xffffffff);
   fm.out_port(1);
   fm.out_group(0);
   fm.flags(0);
   fm.match(m);


   auto out = fluid_msg::EthAddress(llmec_config->X["gateway"]["mac"].get<std::string>());
   fluid_msg::of13::ApplyActions act;
   act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::EthDst(out)));
   act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPv4Dst(to)));
   act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPDSCP(metadata.ipdscp)));
   act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPECN(metadata.ipecn)));
   act.add_action(new fluid_msg::of13::OutputAction(llmec_config->X["ovs_switch"]["external_port"].get<int>(), 1024));
   fm.add_instruction(act);
   fm.add_instruction(new fluid_msg::of13::Meter(meter_id));
   buffer = fm.pack();
   of_conn->send(buffer, fm.length());
   fluid_msg::OFMsg::free_buffer(buffer);
 }

 void OFInterface::redirect_edge_service_dl_meter_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint32_t meter_id, const std::string UE_ip, const uint64_t dl_tunnel, const std::string ENB_ip, std::string from, std::string to, Metadata metadata) {
   Conf* llmec_config = Conf::getInstance();
   uint8_t* buffer;
   fluid_msg::of13::Match m;
   // By default, allow IP traffic
   fluid_msg::of13::EthType eth_type(0x0800);
   fluid_msg::IPAddress ue_ip_addr(UE_ip);
   fluid_msg::of13::IPv4Dst ip_dst(ue_ip_addr);
   fluid_msg::of13::IPv4Src ip_src(to);
   m.add_oxm_field(eth_type);
   m.add_oxm_field(ip_dst);
   m.add_oxm_field(ip_src);

   // Default value for fields below
   fluid_msg::of13::FlowMod fm;
   fm.xid(43);
   fm.cookie(flow_id);
   fm.cookie_mask(0xffffffffffffffff);
   fm.table_id(0);
   fm.command(fluid_msg::of13::OFPFC_ADD);
   fm.idle_timeout(0);
   fm.hard_timeout(0);
   fm.priority(2);
   fm.buffer_id(0xffffffff);
   fm.out_port(1);
   fm.out_group(0);
   fm.flags(0);
   fm.match(m);

   auto out = fluid_msg::EthAddress(llmec_config->X["gateway"]["mac"].get<std::string>());
   fluid_msg::of13::ApplyActions act;
   fluid_msg::of13::TUNNELId dl_tunnel_id(dl_tunnel);
   act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::TUNNELId(dl_tunnel_id)));
   act.add_action(new fluid_msg::of13::OutputAction(llmec_config->X["ovs_switch"]["s1u_port"].get<int>(), 1024));
   fm.add_instruction(act);
   buffer = fm.pack();
   of_conn->send(buffer, fm.length());
   act.add_action(new fluid_msg::of13::OutputAction(llmec_config->X["ovs_switch"]["s1u_port"].get<int>(), 1024));
   fm.add_instruction(act);
   fm.add_instruction(new fluid_msg::of13::Meter(meter_id));
   buffer = fm.pack();
   of_conn->send(buffer, fm.length());
   fluid_msg::OFMsg::free_buffer(buffer);
 }

/*
 * GetMeterTableStatus
 */
void OFInterface::get_meter_stats(fluid_base::OFConnection* of_conn) {
  uint8_t* buffer;
  //MultipartRequestMeter (uint32_t xid, uint16_t flags, uint32_t meter_id)
//  fluid_msg::of13::MultipartRequestMeter mrf(43, 0x0009, fluid_msg::of13::OFPM_ALL);
  fluid_msg::of13::MultipartRequestMeter mrf(43, 0x000a, 0xffffffff);
  buffer = mrf.pack();
  of_conn->send(buffer, mrf.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}
/*
 * GetMeterFeaturesStatus
 */
void OFInterface::get_meter_features_stats(fluid_base::OFConnection* of_conn) {
  uint8_t* buffer;
  //MultipartRequestMeter (uint32_t xid, uint16_t flags)
  fluid_msg::of13::MultipartRequestMeterFeatures mrf(43, 0x000b);
  buffer = mrf.pack();
  of_conn->send(buffer, mrf.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}
/*
 * GetMeterConfigStatus
 */
void OFInterface::get_meter_config_stats(fluid_base::OFConnection* of_conn, uint32_t meter_id) {
  uint8_t* buffer;
  //MultipartRequestMeterConfig (uint32_t xid, uint16_t flags, uint32_t meter_id)
//  fluid_msg::of13::MultipartRequestMeterConfig mrf(43, 0x000a, fluid_msg::of13::OFPM_ALL);
  fluid_msg::of13::MultipartRequestMeterConfig mrf(43, 0x000a, meter_id);
  buffer = mrf.pack();
  of_conn->send(buffer, mrf.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

/*
 *
 */
void OFInterface::flush_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id) {
  uint8_t* buffer;
  fluid_msg::of13::Match m;

  // Default value for fields below
  fluid_msg::of13::FlowMod fm;
  fm.xid(43);
  fm.cookie(flow_id);
  fm.cookie_mask(0xffffffffffffffff);
  //fm.table_id(fluid_msg::of13::OFPTT_ALL);
  fm.table_id(0);
  fm.command(fluid_msg::of13::OFPFC_DELETE);
  fm.idle_timeout(0);
  fm.hard_timeout(0);
  fm.priority(2);
  fm.buffer_id(0xffffffff);
  fm.out_port(fluid_msg::of13::OFPP_ANY);
  fm.out_group(fluid_msg::of13::OFPG_ANY);
  fm.flags(0);
  //fm.match(m);

  buffer = fm.pack();
  of_conn->send(buffer, fm.length());

}

/*
 * Delete entries from switch's meter table.  To delete only a spe‐
              cific  meter,  specify its number as meter.  Otherwise, if meter
              is omitted, or if it is specified as all, then  all  meters  are
              deleted.
 */
void OFInterface::flush_meter(fluid_base::OFConnection* of_conn, uint32_t meter_id) {
	uint8_t* buffer;
  fluid_msg::of13::MeterMod mm;
        //transactionID
	mm.xid(43);
	//command
  mm.command(fluid_msg::of13::OFPMC_DELETE);
        /*
         *MeterBandList
         * kbps__0x0001
         * pkps__0x0002
         * burst_0x0004
         * stats_0x0008
         */
  mm.flags(fluid_msg::of13::OFPMF_KBPS);
	//meterID
  mm.meter_id(meter_id);
  buffer = mm.pack();
  of_conn->send(buffer, mm.length());

}


} // namespace eps
} // namespace core
} // namespace llmec
