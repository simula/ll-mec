#ifndef __STATS_MANAGER_H__
#define __STATS_MANAGER_H__

#include "app.h"
#include "controller.h"

namespace llmec {
namespace app {
namespace stats {

class Stats_manager : public llmec::app::App {
  public:
    Stats_manager(llmec::core::eps::OFInterface &of_interface, llmec::core::eps::Controller &ctrl) : llmec::app::App(of_interface), ctrl(ctrl) {}
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    void start() override;
    std::shared_ptr<std::vector<fluid_msg::of13::FlowStats>> get_flow_stats();
  protected:
    llmec::core::eps::Controller &ctrl;
    std::shared_ptr<std::vector<fluid_msg::of13::FlowStats>> flow_stats_;
};

} // namespace stats
} // namespace app
} // namespace llmec
#endif
