#include "of_interface.h"

namespace llmec {
namespace core {
namespace eps {

#define GATEWAY_MAC "00:24:9b:23:33:a6"
//TODO OpenFlow message field wrapper specifically for LL-MEC
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

void OFInterface::install_default_UE_ul_flow(fluid_base::OFConnection* of_conn, uint64_t ul_tunnel) {
  uint8_t* buffer;
  fluid_msg::of13::Match m;
  // TODO configuration file for s1u port number
  fluid_msg::of13::InPort in_port(2);
  fluid_msg::of13::TUNNELId ul_tunnel_id(ul_tunnel);
  m.add_oxm_field(in_port);
  m.add_oxm_field(ul_tunnel_id);

  fluid_msg::of13::FlowMod fm;
  fm.xid(43);
  fm.cookie(1);
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

  // TODO configuration file for gateway mac
  auto out = fluid_msg::EthAddress(GATEWAY_MAC);
  fluid_msg::of13::ApplyActions act;
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::EthDst(out)));
  // TODO configuration file for external port number
  act.add_action(new fluid_msg::of13::OutputAction(1, 1024));
  fm.add_instruction(act);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

void OFInterface::install_default_UE_dl_flow(fluid_base::OFConnection* of_conn, const std::string UE_ip, const uint64_t dl_tunnel, const std::string ENB_ip) {
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
  // Set cookie to 1 in order to flush flows easily
  fm.cookie(1);
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

  // TODO configuration file for gateway mac
  auto out = fluid_msg::EthAddress(GATEWAY_MAC);
  fluid_msg::of13::ApplyActions act;
  fluid_msg::of13::TUNNELId dl_tunnel_id(dl_tunnel);
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::TUNNELId(dl_tunnel_id)));
  fluid_msg::IPAddress enb_ip_addr(ENB_ip);
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::TUNNELDst(enb_ip_addr)));
  // TODO configuration file for external port number
  act.add_action(new fluid_msg::of13::OutputAction(2, 1024));
  fm.add_instruction(act);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}
void OFInterface::redirect_edge_service_ul_flow(fluid_base::OFConnection* of_conn, uint64_t ul_tunnel, std::string from, std::string to) {
  uint8_t* buffer;
  fluid_msg::of13::Match m;
  // TODO configuration file for s1u port number
  fluid_msg::of13::InPort in_port(2);
  fluid_msg::of13::EthType eth_type(0x0800);
  fluid_msg::of13::TUNNELId ul_tunnel_id(ul_tunnel);
  fluid_msg::of13::IPv4Dst ip_dst(from);
  m.add_oxm_field(in_port);
  m.add_oxm_field(ul_tunnel_id);
  m.add_oxm_field(eth_type);
  m.add_oxm_field(ip_dst);

  fluid_msg::of13::FlowMod fm;
  fm.xid(43);
  fm.cookie(1);
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

  // TODO configuration file for gateway mac
  auto out = fluid_msg::EthAddress(GATEWAY_MAC);
  fluid_msg::of13::ApplyActions act;
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::EthDst(out)));
  // TODO configuration file for external port number
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPv4Dst(to)));
  act.add_action(new fluid_msg::of13::OutputAction(1, 1024));
  fm.add_instruction(act);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

void OFInterface::redirect_edge_service_dl_flow(fluid_base::OFConnection* of_conn, const std::string UE_ip, const uint64_t dl_tunnel, const std::string ENB_ip, std::string from, std::string to) {
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
  // Set cookie to 1 in order to flush flows easily
  fm.cookie(1);
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

  // TODO configuration file for gateway mac
  auto out = fluid_msg::EthAddress(GATEWAY_MAC);
  fluid_msg::of13::ApplyActions act;
  fluid_msg::of13::TUNNELId dl_tunnel_id(dl_tunnel);
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::TUNNELId(dl_tunnel_id)));
  fluid_msg::IPAddress enb_ip_addr(ENB_ip);
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::TUNNELDst(enb_ip_addr)));
  act.add_action(new fluid_msg::of13::SetFieldAction(new fluid_msg::of13::IPv4Src(from)));
  // TODO configuration file for external port number
  act.add_action(new fluid_msg::of13::OutputAction(2, 1024));
  fm.add_instruction(act);
  buffer = fm.pack();
  of_conn->send(buffer, fm.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

void OFInterface::get_flow_stats(fluid_base::OFConnection* of_conn, uint32_t xid, uint8_t table_id, uint64_t cookie, uint64_t cookie_mask, uint32_t out_port) {
  uint8_t* buffer;
  fluid_msg::of13::MultipartRequestFlow mrf(xid, 0, fluid_msg::of13::OFPTT_ALL, fluid_msg::of13::OFPP_ANY, fluid_msg::of13::OFPG_ANY, cookie, cookie_mask);
  buffer = mrf.pack();
  of_conn->send(buffer, mrf.length());
  fluid_msg::OFMsg::free_buffer(buffer);
}

} // namespace eps
} // namespace core
} // namespace llmec
