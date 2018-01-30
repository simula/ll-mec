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
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    void start() override;
    static void create_instance(llmec::core::eps::OFInterface &of_interface);
    static Ue_manager* get_instance();

    /* Add one bearer context to the underlying user plane */
    bool add_bearer(json context);

    /* Redirect one specific bearer from IPv4_A to IPv4_B */
    bool add_redirect_bearer(uint64_t id, json context);

    /* Redirect one specific bearer back if any */
    bool delete_redirect_bearer(uint64_t id);

    /* Return one specific bearer information in JSON array */
    json get_bearer(uint64_t ue_id);

    /* Return all bearers information in JSON array */
    json get_bearer_all();

    /* Delete one specific bearer context from the underlying user plane */
    bool delete_bearer(uint64_t id);

    /* Delete all bearers context */
    bool delete_bearer_all();

  private:
    static Ue_manager* instance;
    Ue_manager(llmec::core::eps::OFInterface &of_interface) : llmec::app::App(of_interface) {}
};

} // namespace uplane
} // namespace app
} // namespace llmec
#endif
