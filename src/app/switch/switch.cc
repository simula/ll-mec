#include "switch.h"

void Switch::event_callback(ControllerEvent* ev) {
  if (ev->get_type() == EVENT_SWITCH_UP) {
      this->of_interface.install_default_flow(ev->of_conn_);
  }
}
