#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "controller_event.h"

class Application {
  public:
    virtual void event_callback(ControllerEvent* ev)=0;
};

#endif
