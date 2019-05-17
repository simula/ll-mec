/*
 * Copyright 2016-2018 Eurecom and Mosaic5G Platforms Authors
 * Licensed to the Mosaic5G under one or more contributor license
 * agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership.
 * The Mosaic5G licenses this file to You under the
 * Apache License, Version 2.0  (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the Mosaic5G:
 *  	contact@mosaic5g.io
 */

/*!
  \file controller_event.h
  \brief captures the events with the LL-MEC controller
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
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
  /*
   * Check if the EVENT value is right!
   */
  EVENT_METER = 4,
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

/* ######################################################
 * This is the MeterEvent Class used in the controller.cc  
 * ######################################################
 * author Mihai IDU
 * company Eurecom
 * email: idumihai16@gmail.com
 * ######################################################
 */
class MeterEvent : public ControllerEvent {
  public:
	  MeterEvent(fluid_base::OFConnection* of_conn, fluid_base::OFHandler* of_handler, void* data, size_t len) :
		  ControllerEvent(of_conn, EVENT_METER) {
			  this->data_ = (uint8_t*) data;
			  this->len_ = len;
			  this->of_handler_ = of_handler;
		  }
	  virtual ~MeterEvent(){
		  this->of_handler_->free_data(this->data_);
	  }
	  fluid_base::OFHandler* of_handler_;
	  uint8_t* data_;
	  size_t len_;
};
/* ######################################################
 * The MeterEvent class end here.
 * ######################################################
 */

} // namespace eps
} // namespace core
} // namespace llmec
#endif
