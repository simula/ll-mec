#ifndef __APP_H__
#define __APP_H__
#include "controller_event.h"
#include "of_interface.h"
#include "task.h"
#include <iostream>

namespace llmec {
namespace app {

class App : public llmec::core::rt::Task {
  public:
    App(llmec::core::eps::OFInterface &of_interface):llmec::core::rt::Task(llmec::core::rt::Policy::DEADLINE), of_interface(of_interface) {
    }
    virtual void event_callback(llmec::core::eps::ControllerEvent* ev)=0;
    void run() {
      if (apply_scheduling_policy() < 0) {
        std::cout << "sched_setattr failed" << std::endl;
      }
      start();
    }
    virtual void start() =0;
  protected:
    llmec::core::eps::OFInterface &of_interface;
};

} // namespace app
} // namespace llmec
#endif
