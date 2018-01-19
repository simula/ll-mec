#ifndef __UE_MANAGER_H__
#define __UE_MANAGER_H__

#include "app.h"
#include "controller.h"

namespace llmec {
namespace app {
namespace uplane {

class Ue_manager : public llmec::app::App {
  public:
    Ue_manager(llmec::core::eps::OFInterface &of_interface) : llmec::app::App(of_interface) {}
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    void start() override;
    void add_ue(uint64_t s1_ul_teid, uint64_t s1_dl_teid, std::string ue_ip, std::string enb_ip);
    void redirect_ue(uint64_t s1_ul_teid, uint64_t s1_dl_teid, std::string ue_ip, std::string enb_ip, std::string from, std::string to);
    void flush_flow(uint64_t cookie);
};

} // namespace uplane
} // namespace app
} // namespace llmec
#endif
