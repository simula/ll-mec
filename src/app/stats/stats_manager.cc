#include "stats_manager.h"
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
  while (true) {
    llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);
    if (of_conn_ != NULL) {
      this->of_interface.get_flow_stats(of_conn_, 43, 0, 1, 0xffffffffffffffff, 1);
      std::chrono::microseconds duration(5000);
      std::this_thread::sleep_for(duration);
    }
  }
}

} // namespace stats
} // namespace app
} // namespace llmec
