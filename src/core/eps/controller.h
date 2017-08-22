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

/*extern volatile sig_atomic_t quit;
  void sigint_handler(int s);


  void wait_for_sigint();*/

namespace llmec {
namespace core {
namespace eps {

class Controller : public fluid_base::OFServer {
  public:
    std::unordered_map<int, std::vector<std::shared_ptr<llmec::app::App>> > event_listeners_;
    // Non-lock map for now
    bool running_;

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
      /*for (std::vector<std::shared_ptr<llmec::app::App>>::iterator it =
          event_listeners_[ev->get_type()].begin();
          it != event_listeners_[ev->get_type()].end();
          it++) {
        ((std::shared_ptr<llmec::app::App>) (it))->event_callback(ev);
      }*/
      delete ev;

    }
};

} // namespace eps
} // namespace core
} // namespace llmec
#endif
