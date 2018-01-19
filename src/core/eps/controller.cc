#include "controller.h"

namespace llmec {
namespace core {
namespace eps {

Controller* Controller::instance = 0;

void Controller::create_instance(const char* address, const int port, const int n_workers, bool secure)
{
  if (instance == 0) {
    instance = new Controller(address, port, n_workers, secure);
  }
}

Controller* Controller::get_instance()
{
  assert(instance);
  return instance;
}

void Controller::stop() {
  running_ = false;
  fluid_base::OFServer::stop();
}
void Controller::connection_callback(fluid_base::OFConnection* ofconn, fluid_base::OFConnection::Event type) {
  if (type == fluid_base::OFConnection::EVENT_STARTED)
    printf("Connection id=%d started\n", ofconn->get_id());

  else if (type == fluid_base::OFConnection::EVENT_ESTABLISHED) {
    printf("Connection id=%d established\n", ofconn->get_id());
    this->conn_id = ofconn->get_id();
  }

  else if (type == fluid_base::OFConnection::EVENT_FAILED_NEGOTIATION)
    printf("Connection id=%d failed version negotiation\n", ofconn->get_id());

  else if (type == fluid_base::OFConnection::EVENT_CLOSED) {
    printf("Connection id=%d closed by the user\n", ofconn->get_id());
    dispatch_event(new SwitchDownEvent(ofconn));
  }

  else if (type == fluid_base::OFConnection::EVENT_DEAD) {
    printf("Connection id=%d closed due to inactivity\n", ofconn->get_id());
    dispatch_event(new SwitchDownEvent(ofconn));
  }
}

void Controller::message_callback(fluid_base::OFConnection* ofconn, uint8_t type, void* data, size_t len) {
  if (type == 10) { // OFPT_PACKET_IN
    dispatch_event(new PacketInEvent(ofconn, this, data, len));
  }
  else if (type == 6) { // OFPT_FEATURES_REPLY
    dispatch_event(new SwitchUpEvent(ofconn, this, data, len));
  }
  else if (type == 19) { //OFPT_MULTIPART_REPLY
    dispatch_event(new MultipartReplyEvent(ofconn, this, data, len));
  }
}

void Controller::register_for_event(const std::shared_ptr<llmec::app::App>& app, int event_type) {
  event_listeners_[event_type].push_back(app);
}

} // namespace eps
} // namespace core
} // namespace llmec
