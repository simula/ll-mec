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

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// #include <boost/unordered_map.hpp>
#include <unordered_map>
#include <string.h>
#include <list>
#include <signal.h>
#include <unistd.h>
#include <memory>

#include <fluid/OFServer.hh>

#include "app.h"

namespace llmec {
namespace core {
namespace eps {

class Controller : public fluid_base::OFServer {
  public:
    static Controller* get_instance();
    static void create_instance(const char* address, const int port, const int n_workers, bool secure);
    std::unordered_map<int, std::vector<std::shared_ptr<llmec::app::App>> > event_listeners_;
    // TODO Need to be refactor for multiple switch
    // Assume only one switch for now
    int conn_id;
    // Non-lock map for now
    bool running_;

    virtual void connection_callback(fluid_base::OFConnection* of_conn, fluid_base::OFConnection::Event type);
    virtual void message_callback(fluid_base::OFConnection* of_conn, uint8_t type, void* data, size_t len);
    void register_for_event(const std::shared_ptr<llmec::app::App>& app, int event_type);

    void stop();

    inline void dispatch_event(ControllerEvent* ev) {
      if (not this->running_) {
        delete ev;
        return;
      }
      for (auto app : event_listeners_[ev->get_type()]) {
        app->event_callback(ev);
      }
      delete ev;

    }
  private:
    static Controller* instance;
    Controller(
        const char* address = "0.0.0.0",
        const int port = 6653,
        const int n_workers = 4,
        bool secure = false):
      fluid_base::OFServer(
          address,
          port,
          n_workers,
          secure,
          fluid_base::OFServerSettings().supported_version(1).supported_version(4).keep_data_ownership(false)) {
        this->running_ = true;
      }
};

} // namespace eps
} // namespace core
} // namespace llmec
#endif
