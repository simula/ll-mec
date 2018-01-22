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

#include "conf.h"
#include "stats_manager.h"
#include "spdlog.h"
#include "ue_manager.h"

#include <iostream>
#include <fluid/of13msg.hh>
#include <fluid/of13/openflow-13.h>
#include <chrono>

namespace llmec {
namespace app {
namespace stats {

void Stats_manager::event_callback(llmec::core::eps::ControllerEvent* ev) {
  if (ev->get_type() == llmec::core::eps::EVENT_MULTIPART_REPLY) {
    fluid_msg::of13::MultipartReplyFlow reply;
    reply.unpack(((llmec::core::eps::MultipartReplyEvent*)ev)->data_);
    this->flow_stats_ = std::make_shared<std::vector<fluid_msg::of13::FlowStats>>(reply.flow_stats());
  }
}

std::shared_ptr<std::vector<fluid_msg::of13::FlowStats>> Stats_manager::get_flow_stats() {
  return this->flow_stats_;
}
void Stats_manager::start() {
  spdlog::get("ll-mec")->info("Stats manager started");
  while (true) {
    llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);
    Conf* llmec_config = Conf::getInstance();
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    if (of_conn_ != NULL) {
      std::vector<uint64_t> ue_list = ue_manager->get_ue_list();
      for (auto each:ue_list)
        this->of_interface.get_flow_stats(of_conn_, 43, 0, each, 0xffffffffffffffff, llmec_config->X["ovs_switch"]["s1u_port"]);
//      this->of_interface.get_flow_stats(of_conn_, 43, 0, 1, 0xffffffffffffffff, llmec_config->X["ovs_switch"]["external_port"]);
      std::this_thread::sleep_for(std::chrono::microseconds(2000000));
    }
  }
}

} // namespace stats
} // namespace app
} // namespace llmec
