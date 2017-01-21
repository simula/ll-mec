#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "application.h"

class Switch : public Application {
public:
  Switch(OFInterface &of_interface) : Application(of_interface) {}
  void event_callback(ControllerEvent* ev);
  void run() override;
};
#endif
