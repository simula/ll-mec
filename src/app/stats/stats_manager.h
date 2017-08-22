#ifndef __STATS_MANAGER_H__
#define __STATS_MANAGER_H__

#include "app.h"

namespace llmec {
namespace app {
namespace stats {

class Stats_manager : public llmec::app::App {
  public:
    Stats_manager(llmec::core::eps::OFInterface &of_interface) : llmec::app::App(of_interface) {}
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    void start() override;
};

} // namespace stats
} // namespace app
} // namespace llmec
#endif
