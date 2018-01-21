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
