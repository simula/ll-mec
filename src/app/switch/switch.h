#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "app.h"

namespace llmec {
namespace app {
namespace _switch {

class Switch : public llmec::app::App {
  public:
    Switch(llmec::core::eps::OFInterface &of_interface) : llmec::app::App(of_interface) {}
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    void start() override;
};

} // namespace _switch
} // namespace app
} // namespace llmec
#endif
