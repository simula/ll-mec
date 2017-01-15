#ifndef __SGWC_H__
#define __SGWC_H__

#include "application.h"

class SGWC : public Application {
public:
  void event_callback(ControllerEvent* ev);
};
#endif
