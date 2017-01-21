#include <iostream>
#include "controller.h"
#include "sgwc.h"
#include "switch.h"
#include "of_interface.h"
#include "controller_event.h"

int main(){
  Controller ctrl("0.0.0.0", 6653, 2);

  //OpenFlow driver interface init
  OFInterface of_interface;

  //TODO Application manager and low latency scheduler
  //Initialize application
  SGWC sgwc(of_interface);
  Switch swt(of_interface);

  //Register event for application
  ctrl.register_for_event(&sgwc, EVENT_PACKET_IN);
  ctrl.register_for_event(&swt, EVENT_PACKET_IN);

  //Controller start
  ctrl.start(true);

  //wait_for_sigint();
  //ctrl.stop();
  return 0;
}
