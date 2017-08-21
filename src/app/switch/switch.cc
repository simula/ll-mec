#include "switch.h"
#include <iostream>

namespace llmec {
namespace app {
namespace _switch {

void Switch::event_callback(llmec::core::eps::ControllerEvent* ev) {
  if (ev->get_type() == llmec::core::eps::EVENT_SWITCH_UP) {
    this->of_interface.install_default_flow(ev->of_conn_);
  }
}
void Switch::start() {
  while(true){
    //std::cout<<"Switch"<<std::endl;
  }
}

} // namespace _switch
} // namespace app
} // namespace llmec
