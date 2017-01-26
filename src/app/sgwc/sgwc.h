#ifndef __SGWC_H__
#define __SGWC_H__

#include "app.h"

class SGWC : public App {
public:
  SGWC(OFInterface &of_interface) : App(of_interface) {}
  void event_callback(ControllerEvent* ev);
  void start() override;
};
#endif
