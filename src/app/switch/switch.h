#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "app.h"

class Switch : public App {
public:
  Switch(OFInterface &of_interface) : App(of_interface) {}
  void event_callback(ControllerEvent* ev);
  void start() override;
};
#endif
