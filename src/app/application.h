#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "controller_event.h"
#include "of_interface.h"

class Application {
  public:
    Application(OFInterface &of_interface):of_interface(of_interface) {
    }
    virtual void event_callback(ControllerEvent* ev)=0;
    virtual void run()=0;
  protected:
    OFInterface &of_interface;
};

#endif
