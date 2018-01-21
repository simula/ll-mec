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

#ifndef __CONTROLLER_EVENT_H__
#define __CONTROLLER_EVENT_H__

#include <fluid/OFServer.hh>

namespace llmec {
namespace core {
namespace eps {

typedef enum {
  EVENT_PACKET_IN = 0,
  EVENT_SWITCH_DOWN = 1,
  EVENT_SWITCH_UP = 2,
  EVENT_MULTIPART_REPLY = 3,
} EventType;

class ControllerEvent {
  public:
    ControllerEvent(fluid_base::OFConnection* of_conn, EventType event_type) {
      this->of_conn_ = of_conn;
      this->event_type_ = event_type;
    }
    virtual ~ControllerEvent() {}

    virtual int get_type() {
      return this->event_type_;
    }

    fluid_base::OFConnection* of_conn_;

  private:
    EventType event_type_;
};

class PacketInEvent : public ControllerEvent {
  public:
    PacketInEvent(fluid_base::OFConnection* of_conn, fluid_base::OFHandler* of_handler, void* data, size_t len) :
      ControllerEvent(of_conn, EVENT_PACKET_IN) {
        this->data_ = (uint8_t*) data;
        this->len_ = len;
        this->of_handler_ = of_handler;
      }

    virtual ~PacketInEvent() {
      this->of_handler_->free_data(this->data_);
    }

    fluid_base::OFHandler* of_handler_;
    uint8_t* data_;
    size_t len_;
};

class SwitchUpEvent : public ControllerEvent {
  public:
    SwitchUpEvent(fluid_base::OFConnection* of_conn, fluid_base::OFHandler* of_handler, void* data, size_t len) :
      ControllerEvent(of_conn, EVENT_SWITCH_UP) {
        this->data_ = (uint8_t*) data;
        this->len_ = len;
        this->of_handler_ = of_handler;
      }

    virtual ~SwitchUpEvent() {
      this->of_handler_->free_data(this->data_);
    }

    fluid_base::OFHandler* of_handler_;
    uint8_t* data_;
    size_t len_;
};

class SwitchDownEvent : public ControllerEvent {
  public:
    SwitchDownEvent(fluid_base::OFConnection* of_conn) :
      ControllerEvent(of_conn, EVENT_SWITCH_DOWN) {}
};

class MultipartReplyEvent : public ControllerEvent {
  public:
    MultipartReplyEvent(fluid_base::OFConnection* of_conn, fluid_base::OFHandler* of_handler, void* data, size_t len) :
      ControllerEvent(of_conn, EVENT_MULTIPART_REPLY) {
        this->data_ = (uint8_t*) data;
        this->len_ = len;
        this->of_handler_ = of_handler;
      }

    virtual ~MultipartReplyEvent() {
      this->of_handler_->free_data(this->data_);
    }

    fluid_base::OFHandler* of_handler_;
    uint8_t* data_;
    size_t len_;
};

} // namespace eps
} // namespace core
} // namespace llmec
#endif
