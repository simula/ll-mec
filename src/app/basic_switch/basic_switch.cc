#include "basic_switch.h"
#include <iostream>

namespace llmec {
namespace app {
namespace basic_switch {

void Basic_switch::event_callback(llmec::core::eps::ControllerEvent* ev) {
  if (ev->get_type() == llmec::core::eps::EVENT_SWITCH_UP) {
    this->of_interface.install_default_flow(ev->of_conn_);
  }
}
void Basic_switch::start() {
  while(true){
    //std::cout<<"Switch"<<std::endl;
  }
}

} // namespace basic_switch
} // namespace app
} // namespace llmec
