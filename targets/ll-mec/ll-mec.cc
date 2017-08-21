#include <iostream>
#include "controller.h"
#include "sgwc.h"
#include "basic_switch.h"
#include "of_interface.h"
#include "controller_event.h"
#include <thread>

int main(){
  llmec::core::eps::Controller ctrl("0.0.0.0", 6653, 2);

  //OpenFlow driver interface init
  llmec::core::eps::OFInterface of_interface;

  //TODO Application manager and low latency scheduler
  //Initialize application
  //SGWC sgwc(of_interface);
  llmec::app::basic_switch::Basic_switch swt(of_interface);

  //Register event for application
  //ctrl.register_for_event(&sgwc, EVENT_PACKET_IN);
  ctrl.register_for_event(&swt, llmec::core::eps::EVENT_SWITCH_UP);

  //std::thread sgwc_app(&SGWC::run, &sgwc);
  std::thread swt_app(&llmec::app::basic_switch::Basic_switch::run, &swt);

  //Controller start
  ctrl.start(true);

  //wait_for_sigint();
  //ctrl.stop();
  return 0;
}
