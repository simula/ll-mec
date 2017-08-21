#ifndef __SGWC_H__
#define __SGWC_H__

#include "app.h"

namespace llmec {
namespace app {
namespace sgwc {

class SGWC : public llmec::app::App {
  public:
    SGWC(llmec::core::eps::OFInterface &of_interface) : llmec::app::App(of_interface) {}
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    void start() override;
};

} // namespace sgwc
} // namespace app
} // namespace llmec
#endif
