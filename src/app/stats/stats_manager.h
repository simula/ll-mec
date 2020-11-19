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
  \file stats_manger.h
  \brief defining sets to manage the state of users 
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#ifndef __STATS_MANAGER_H__
#define __STATS_MANAGER_H__

#include "app.h"
#include "controller.h"
#include "json.h"

#include <mutex>

using json = nlohmann::json;

namespace llmec {
namespace app {
namespace stats {

class Stats_manager : public llmec::app::App {
  public:
    Stats_manager(llmec::core::eps::OFInterface &of_interface,
                  llmec::event::subscription &ev);
    void event_callback(llmec::core::eps::ControllerEvent* ev) {};
    void handle_multipart_reply(llmec::core::eps::MultipartReplyEvent ev);
    void start() override;
    json get_flow_stats(uint64_t id);
  private:
    /* flow_stats protected by mutex lock */
    std::mutex flow_stats_lock;
    /* OVS cookie is the key here and filled previously with MEC ID in UE manager */
    std::map<uint64_t, json> flow_stats_;
    std::map<uint64_t, uint64_t> bearers_switch_;
    std::map<uint64_t, std::set<uint64_t>> switch_bearers_;
};

} // namespace stats
} // namespace app
} // namespace llmec
#endif
