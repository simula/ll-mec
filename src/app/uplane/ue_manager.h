#ifndef __UE_MANAGER_H__
#define __UE_MANAGER_H__

#include <mutex>
#include <unordered_map>

#include "app.h"
#include "controller.h"
#include "json.h"

using json = nlohmann::json;

namespace llmec {
namespace app {
namespace uplane {

class Ue_manager : public llmec::app::App {
  public:
    Ue_manager(llmec::core::eps::OFInterface &of_interface) : llmec::app::App(of_interface) {}
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    void start() override;
    bool add_ue(uint64_t eps_bearer_id, std::string imsi, uint64_t s1_ul_teid, uint64_t s1_dl_teid, std::string ue_ip, std::string enb_ip);
    bool redirect_ue(uint64_t s1_ul_teid, uint64_t s1_dl_teid, std::string ue_ip, std::string enb_ip, std::string from, std::string to);
    bool flush_flow(uint64_t eps_bearer_id);
  private:
    std::unordered_map<uint64_t, json> ue_context;
    std::mutex ue_context_lock;
};

} // namespace uplane
} // namespace app
} // namespace llmec
#endif
