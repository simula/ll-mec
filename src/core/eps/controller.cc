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
  \file conroller.cc
  \brief OF controller 
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#include "controller.h"
#include "spdlog.h"

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
    spdlog::get("ll-mec")->info("Switch id={} started", ofconn->get_id());

  else if (type == fluid_base::OFConnection::EVENT_ESTABLISHED) {
    spdlog::get("ll-mec")->info("Switch id={} established", ofconn->get_id());
    this->conn_id = ofconn->get_id();
  }

  else if (type == fluid_base::OFConnection::EVENT_FAILED_NEGOTIATION)
    spdlog::get("ll-mec")->info("Switch id=%d failed version negotiation", ofconn->get_id());

  else if (type == fluid_base::OFConnection::EVENT_CLOSED) {
    spdlog::get("ll-mec")->info("Switch id=%d closed by the user", ofconn->get_id());
    dispatch_event(new SwitchDownEvent(ofconn));
  }

  else if (type == fluid_base::OFConnection::EVENT_DEAD) {
    spdlog::get("ll-mec")->info("Switch id=%d closed due to inactivity", ofconn->get_id());
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
