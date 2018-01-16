#include "basic_switch.h"
#include <iostream>

namespace llmec {
namespace app {
namespace basic_switch {

void Basic_switch::event_callback(llmec::core::eps::ControllerEvent* ev) {
  if (ev->get_type() == llmec::core::eps::EVENT_SWITCH_UP) {
    this->of_interface.install_default_flow(ev->of_conn_);
    switch_set_.insert(ev->of_conn_->get_id());
  }
}
std::unordered_set<int> Basic_switch::get_switch_list() {
  return this->switch_set_;
}
void Basic_switch::start() {
  while(true){
    //std::cout<<"Switch"<<std::endl;
  }
}

} // namespace basic_switch
} // namespace app
} // namespace llmec
