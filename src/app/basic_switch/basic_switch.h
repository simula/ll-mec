#ifndef __BASIC_SWITCH_H__
#define __BASIC_SWITCH_H__
#include <unordered_set>
#include "app.h"

namespace llmec {
namespace app {
namespace basic_switch {

class Basic_switch : public llmec::app::App {
  public:
    Basic_switch(llmec::core::eps::OFInterface &of_interface) : llmec::app::App(of_interface) {}
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    std::unordered_set<int> get_switch_list();
    void start() override;
  private:
    std::unordered_set<int> switch_set_;
};

} // namespace basic_switch
} // namespace app
} // namespace llmec
#endif
