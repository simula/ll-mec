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
  \file switch_manager.cc
  \brief managing the status of the OVS switch based on its ID
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/


#include <iostream>
#include "switch_manager.h"
#include "conf.h"
#include "spdlog.h"
#include "context_manager.h"

namespace llmec {
namespace app {
namespace switch_manager {

Switch_manager::Switch_manager(llmec::core::eps::OFInterface &of_interface,
                               llmec::event::subscription &ev)
  : llmec::app::App(of_interface, ev) {
  event_sub.subscribe_openflow_switch_up(
      boost::bind(&Switch_manager::handle_switch_up, this, _1));
  event_sub.subscribe_openflow_switch_down(
      boost::bind(&Switch_manager::handle_switch_down, this, _1));
}

void Switch_manager::handle_switch_up(const llmec::core::eps::SwitchUpEvent& ev) {
  const bool support_meter = Conf::getInstance()->X["ovs_switch"]["support_meter"].get<bool>();
  this->of_interface.install_default_flow(ev.of_conn_);
  spdlog::get("ll-mec")->info("Switch id={} installed default flow", ev.of_conn_->get_id());
  //define a default meter rule of 10GB rate with meterID=DEFAULT_MT_ID
  //this will be the default generic meter assigned into the first set of flows
  if (support_meter)
    this->of_interface.install_default_meter_drop(ev.of_conn_, DEFAULT_MT_ID);
  llmec::data::Context_manager::get_instance()->add_switch(ev.of_conn_->get_id());
}

void Switch_manager::handle_switch_down(const llmec::core::eps::SwitchDownEvent& ev) {
  const bool support_meter = Conf::getInstance()->X["ovs_switch"]["support_meter"].get<bool>();
  /* the switch id, mec id are not related together for the moment */
  if (support_meter)
    this->of_interface.flush_meter(ev.of_conn_, DEFAULT_MT_ID);
  spdlog::get("ll-mec")->info("Switch id={} flushed flow", ev.of_conn_->get_id());
  llmec::data::Context_manager::get_instance()->delete_switch(ev.of_conn_->get_id());
}

void Switch_manager::start() {
  while(true){
  }
}

} // namespace basic_switch
} // namespace app
} // namespace llmec
