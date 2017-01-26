#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "controller_event.h"
#include "of_interface.h"
#include "task.h"
#include <iostream>

class Application : public Task {
  public:
    Application(OFInterface &of_interface):Task(Policy::DEADLINE), of_interface(of_interface) {
    }
    virtual void event_callback(ControllerEvent* ev)=0;
    void run() {
      if (apply_scheduling_policy() < 0) {
        std::cout << "sched_setattr failed" << std::endl;
      }
      start();
    }
    virtual void start() =0;
  protected:
    OFInterface &of_interface;
};

#endif
