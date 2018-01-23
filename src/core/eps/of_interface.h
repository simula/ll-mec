/* The MIT License (MIT)

   Copyright (c) 2018 Anta Huang (anta.huang@eurecom.fr)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

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
    void install_default_UE_ul_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint64_t ul_tunnel_id);
    void install_default_UE_dl_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, std::string UE_ip, uint64_t dl_tunnel_id, std::string ENB_ip);
    void redirect_edge_service_ul_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, uint64_t ul_tunnel_id, std::string from, std::string to);
    void redirect_edge_service_dl_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id, std::string UE_ip, uint64_t dl_tunnel_id, std::string ENB_ip, std::string from, std::string to);
    void get_flow_stats(fluid_base::OFConnection* of_conn, uint32_t xid, uint8_t table_id, uint64_t cookie, uint64_t cookie_mask);
    void flush_flow(fluid_base::OFConnection* of_conn, uint64_t flow_id);
};

} // namespace eps
} // namespace core
} // namespace llmec
#endif
