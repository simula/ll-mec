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
  \brief managing the users and bearers, and their associations to different slices
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
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

class Ue_manager : public llmec::app::App {
  public:
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    void start() override;
    static void create_instance(llmec::core::eps::OFInterface &of_interface);
    static Ue_manager* get_instance();

    /* Add one bearer context to the underlying user plane */
    bool add_bearer(json context);

    /* Redirect one specific bearer from IPv4_A to IPv4_B */
    bool add_redirect_bearer(uint64_t id, uint32_t meterid, json context);

    /* Redirect one specific bearer back if any */
    bool delete_redirect_bearer(uint64_t id);

    /* Return one specific bearer information in JSON array */
    json get_bearer(uint64_t ue_id);

    /* Return all bearers information in JSON array */
    json get_bearer_all();

    /* Delete one specific bearer context from the underlying user plane */
    bool delete_bearer(uint64_t id);

    /*Delete an specic meter ID */
    bool delete_meter_table(uint32_t meterid);

    /* Delete all bearers context */
    bool delete_bearer_all();

    /* Return one specific slice information in JSON array */
    json get_slice(uint64_t slice_id);

    /* Return all slices information in JSON array */
    json get_slice_all();

    /* Get the bearer id list */
    std::vector<uint64_t> get_bearer_id_list();

    /* Get the id by IMSI and bearer */
    uint64_t get_id(std::string imsi, uint64_t eps_bearer_id);

    /*Get the meterid by IMSI and bearer*/
//    uint32_t get_meterid(uint32_t meter_id);

    /* Check if ID exists in LLMEC context */
    bool id_exist(uint64_t id);

  private:
    static Ue_manager* instance;
    Ue_manager(llmec::core::eps::OFInterface &of_interface) : llmec::app::App(of_interface) {}
};

} // namespace uplane
} // namespace app
} // namespace llmec
#endif
