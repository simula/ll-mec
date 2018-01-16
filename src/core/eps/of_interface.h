#ifndef __OF_INTERFACE_H__
#define __OF_INTERFACE_H__

#include <fluid/OFServer.hh>
#include <fluid/of10msg.hh>
#include <fluid/of13msg.hh>

//LL-MEC OpenFlow interface
namespace llmec {
namespace core {
namespace eps {

class OFInterface {
  public:
    void install_flow_mod(fluid_msg::of10::PacketIn &pi, fluid_base::OFConnection* of_conn, uint64_t src, uint64_t dst, uint16_t out_port);
    void install_flow_mod(fluid_msg::of13::PacketIn &pi, fluid_base::OFConnection* of_conn, uint64_t src, uint64_t dst, uint16_t out_port);
    void install_default_flow(fluid_base::OFConnection* of_conn);
    void install_default_UE_ul_flow(fluid_base::OFConnection* of_conn, uint64_t ul_tunnel_id);
    void install_default_UE_dl_flow(fluid_base::OFConnection* of_conn, std::string UE_ip, uint64_t dl_tunnel_id, std::string ENB_ip);
};

} // namespace eps
} // namespace core
} // namespace llmec
#endif
