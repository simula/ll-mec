#ifndef __APPLICATION_HH__
#define __APPLICATION_HH__
#include "ControllerEvent.hh"

class Application {
  public:
    virtual void event_callback(ControllerEvent* ev);
};

#endif
