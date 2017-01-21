#ifndef __SGWC_H__
#define __SGWC_H__

#include "application.h"

class SGWC : public Application {
public:
  SGWC(OFInterface &of_interface) : Application(of_interface) {}
  void event_callback(ControllerEvent* ev);
  void run() override;
};
#endif
