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
  \file stats_manager.cc
  \brief manages the state of users in terms of flow statistics
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#include "conf.h"
#include "stats_manager.h"
#include "spdlog.h"
#include "ue_manager.h"

#include <iostream>
#include <fluid/of13msg.hh>
#include <fluid/of13/openflow-13.h>
#include <chrono>

namespace llmec {
namespace app {
namespace stats {

void Stats_manager::event_callback(llmec::core::eps::ControllerEvent* ev) {
  if (ev->get_type() == llmec::core::eps::EVENT_MULTIPART_REPLY) {
//    spdlog::get("ll-mec")->info("Switch id={} installed default flow", ev->of_conn_->get_id());
    fluid_msg::of13::MultipartReplyFlow reply;
    reply.unpack(((llmec::core::eps::MultipartReplyEvent*)ev)->data_);
    this->flow_stats_lock.lock();
    for (auto each:reply.flow_stats()) {
      json flow_stats;
      flow_stats["table_id"] = each.table_id();
      flow_stats["duration_sec"] = each.duration_sec();
      flow_stats["priority"] = each.priority();
      flow_stats["packet_count"] = each.packet_count();
      flow_stats["byte_count"] = each.byte_count();
      /* Cookie is used as the identities in OVS and filled with MEC id in UE manager */
      if (each.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_TUNNEL_ID) != NULL)
        this->flow_stats_[each.cookie()]["ul"] = flow_stats;
      else
        this->flow_stats_[each.cookie()]["dl"] = flow_stats;
      this->flow_stats_[each.cookie()]["switch_id"] = ev->of_conn_->get_id();
      this->bearers_switch_[each.cookie()] = ev->of_conn_->get_id();
      this->switch_bearers_[ev->of_conn_->get_id()].insert(each.cookie());
    }
    this->flow_stats_lock.unlock();
  }
}

json Stats_manager::get_flow_stats(uint64_t id) {
  json response;
  this->flow_stats_lock.lock();
  if (this->flow_stats_.count(id) > 0)
    response = this->flow_stats_[id];
  this->flow_stats_lock.unlock();
  return response;
}

void Stats_manager::start() {
  spdlog::get("ll-mec")->debug("Stats manager started");
  while (true) {
    llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);
    Conf* llmec_config = Conf::getInstance();
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    if (of_conn_ != NULL) {
      this->of_interface.get_flow_stats(of_conn_, 43, 0, 1, 0xffffffffffff0000);
//      this->of_interface.get_meter_stats(of_conn_);
//      this->of_interface.get_meter_features_stats(of_conn_);
//      this->of_interface.get_meter_config_stats(of_conn_, 0xffffffff);
    }
    std::this_thread::sleep_for(std::chrono::microseconds(20000000));
  }
}

} // namespace stats
} // namespace app
} // namespace llmec
