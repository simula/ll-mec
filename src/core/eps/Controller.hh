#ifndef __CONTROLLER_HH__
#define __CONTROLLER_HH__

// #include <boost/unordered_map.hpp>
#include <unordered_map>
#include <string.h>
#include <list>
#include <signal.h>
#include <unistd.h>

#include "fluid/OFServer.hh"

#include "Application.hh"

extern volatile sig_atomic_t quit;
void sigint_handler(int s);


void wait_for_sigint();


class Controller : public fluid_base::OFServer {
  public:
    std::unordered_map<int, std::vector<Application*> > event_listeners;
    // Non-lock map for now
    bool running;

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
        this->running = true;
      }

    virtual void connection_callback(fluid_base::OFConnection* ofconn, fluid_base::OFConnection::Event type);
    virtual void message_callback(fluid_base::OFConnection* ofconn, uint8_t type, void* data, size_t len);
    void register_for_event(Application* app, int event_type);

    void stop();

    inline void dispatch_event(ControllerEvent* ev);
};

#endif
