/* The MIT License (MIT)

   Copyright (c) 2018 Anta Huang (anta.huang@eurecom.fr)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

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
    bool add_ue(uint64_t ue_id, std::string imsi, uint64_t s1_ul_teid, uint64_t s1_dl_teid, std::string ue_ip, std::string enb_ip);
    bool redirect_ue(uint64_t ue_id, uint64_t s1_ul_teid, uint64_t s1_dl_teid, std::string ue_ip, std::string enb_ip, std::string from, std::string to);
    bool delete_redirect_ue(uint64_t ue_id);
    json get_ue(uint64_t ue_id);
    json get_ue_all();
    bool delete_ue(uint64_t ue_id);
    bool delete_ue_all();
  private:
    std::unordered_map<uint64_t, json> ue_context;
    std::mutex ue_context_lock;
};

} // namespace uplane
} // namespace app
} // namespace llmec
#endif
