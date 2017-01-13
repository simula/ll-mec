#ifndef __CONTROLLER_EVENT_HH__
#define __CONTROLLER_EVENT_HH__

#include <fluid/OFServer.hh>

typedef enum {
  EVENT_PACKET_IN = 0,
  EVENT_SWITCH_DOWN = 1,
  EVENT_SWITCH_UP = 2,
} EventType;

class ControllerEvent {
  public:
    ControllerEvent(fluid_base::OFConnection* ofconn, EventType eventtype) {
      this->ofconn_ = ofconn;
      this->eventtype_ = eventtype;
    }
    virtual ~ControllerEvent() {}

    virtual int get_type() {
      return this->eventtype_;
    }

    fluid_base::OFConnection* ofconn_;

  private:
    EventType eventtype_;
};

class PacketInEvent : public ControllerEvent {
  public:
    PacketInEvent(fluid_base::OFConnection* ofconn, fluid_base::OFHandler* ofhandler, void* data, size_t len) :
      ControllerEvent(ofconn, EVENT_PACKET_IN) {
        this->data_ = (uint8_t*) data;
        this->len_ = len;
        this->ofhandler_ = ofhandler;
      }

    virtual ~PacketInEvent() {
      this->ofhandler_->free_data(this->data_);
    }

    fluid_base::OFHandler* ofhandler_;
    uint8_t* data_;
    size_t len_;
};

class SwitchUpEvent : public ControllerEvent {
  public:
    SwitchUpEvent(fluid_base::OFConnection* ofconn, fluid_base::OFHandler* ofhandler, void* data, size_t len) :
      ControllerEvent(ofconn, EVENT_SWITCH_UP) {
        this->data_ = (uint8_t*) data;
        this->len_ = len;
        this->ofhandler_ = ofhandler;
      }

    virtual ~SwitchUpEvent() {
      this->ofhandler_->free_data(this->data_);
    }

    fluid_base::OFHandler* ofhandler_;
    uint8_t* data_;
    size_t len_;
};

class SwitchDownEvent : public ControllerEvent {
  public:
    SwitchDownEvent(fluid_base::OFConnection* ofconn) :
      ControllerEvent(ofconn, EVENT_SWITCH_DOWN) {}
};

#endif
