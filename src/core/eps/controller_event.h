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

} // namespace eps
} // namespace core
} // namespace llmec
#endif
