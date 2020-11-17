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
  \file ue_manager.h
  \
  \author Mihai IDU and N. Nikaein
  \company Eurecom
  \email: idumihai16@gmail.com, navid.nikaein@eurecom.fr
*/

#ifndef __UE_MANAGER_H__
#define __UE_MANAGER_H__

#include <mutex>
#include <unordered_map>

#include "app.h"
#include "controller.h"
#include "json.h"

using json = nlohmann::json;

namespace llmec {
namespace app {
namespace uplane {

class Meter_manager : public llmec::app::App {
  public:
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    void start() override;
    static void create_instance(llmec::core::eps::OFInterface &of_interface);
    static Ue_manager* get_instance();

    /* Add one meter of type drop */
    bool add_meter_drop(json context);

    /* Add one meter of type dscp */
    bool add_meter_dscp(json context);

    /* Delete a specific meter */
    bool delete_meter(uint32_t meter_id);

    /* Return one specific bearer information in JSON array */
    json get_bearer(uint64_t ue_id);

    /* Return all meters information in JSON array */
    json get_meter_stats();

    /* Delete all meters  */
    bool delete_meter_all();

    /*Get the meterid by IMSI and bearer*/
    uint32_t get_meter_id(std::string imsi, uint32_t eps_meter_id);

  private:
    static Ue_manager* instance;
    Ue_manager(llmec::core::eps::OFInterface &of_interface,
               llmec::event::subscription &ev)
      : llmec::app::App(of_interface, ev) {}
};

} // namespace meter_manager
} // namespace app
} // namespace llmec
#endif
