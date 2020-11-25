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
  \file meter_manager.cc
  \
  \author Mihai IDU and N. Nikaein
  \company Eurecom
  \email: idumihai16@gmail.com, navid.nikaein@eurecom.fr
*/

#include <iostream>

#include "meter_manager.h"
#include "context_manager.h"
#include "spdlog.h"
#include "metadata.h"

namespace llmec {
namespace app {
namespace meter_manager {

void Meter_manager::start()
{
  //TODO:
}

bool Meter_manager::add_meter_drop(json context){
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();

  uint32_t meterrate = context["meter_rate"].get<int>();
  uint32_t meterid = context_manager->get_meter_id(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>());
  uint32_t meterburstsize = context["burst_size"].get<int>();
  spdlog::get("ll-mec")->debug("bearer {}", id);
  spdlog::get("ll-mec")->debug("meter {}", meterid); //output the meterid value for the user
  spdlog::get("ll-mec")->debug("meter rate {}", meterrate);
  spdlog::get("ll-mec")->debug("meter burst_size {}", meterburstsize);
  /* Bearer already exists. Remove it and then add (Overwrite) */
  if (meterid != 0) {
    for (auto each:context_manager->get_switch_set()) {
      fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
      if (of_conn_ == nullptr || !of_conn_->is_alive())
        continue;
      this->of_interface.install_default_meter_drop(of_conn_,meterid);
      this->of_interface.modify_meter_mod_drop(of_conn_, meterid, meterrate, meterburstsize);
    }
  }
  else {
    // if the meterID value is 0 in the future operations it will be used the default meterTable
    meterid = 1;
  }
  return true;
}

bool Meter_manager::add_meter_dscp(json context){
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();

  uint32_t meterrate = context["meter_rate"].get<int>();
  uint32_t meterid = context_manager->get_meter_id(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>());
  uint32_t meterburstsize = context["burst_size"].get<int>();
  spdlog::get("ll-mec")->debug("bearer {}", id);
  spdlog::get("ll-mec")->debug("meter {}", meterid); //output the meterid value for the user
  spdlog::get("ll-mec")->debug("meter rate {}", meterrate);
  spdlog::get("ll-mec")->debug("meter burst_size {}", meterburstsize);
  /* Bearer already exists. Remove it and then add (Overwrite) */
  if (meterid != 0) {
    for (auto each:context_manager->get_switch_set()) {
      fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
      if (of_conn_ == nullptr || !of_conn_->is_alive())
        continue;
      this->of_interface.install_default_meter_dscp(of_conn_,meterid);
      this->of_interface.modify_meter_mod_dscp(of_conn_, meterid, meterrate, meterburstsize);
    }
  }
  else {
// if the meterID value is 0 in the future operations it will be used the default meterTable
    meterid = 1;
  }
  return true;
}

bool Meter_manager::delete_meter_all() {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();

  /* flush meters for each ue and clear the map */
  std::vector<uint64_t> id_list = context_manager->get_id_list();
  for (auto id:id_list) {
    for (auto switch_id:context_manager->get_switch_set()) {
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(switch_id);
    if (of_conn_ == nullptr || !of_conn_->is_alive())
      continue;
      // this->of_interface.flush_flow(of_conn_, id);
      this->of_interface.flush_meter(of_conn_,meterid);
    }
  }
  context_manager->clean();
  spdlog::get("ll-mec")->info("Removed all meters");
  return true;
}


//retrive the meter stats
bool Meter_manager::get_meter_stats(){
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  uint32_t meterid = context_manager->get_meter_id(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>());
  this->of_interface.get_meter_stats(of_conn_,meterid);
  return true;
}


Meter_manager* Meter_manager::instance = 0;

void Meter_manager::create_instance(llmec::core::eps::OFInterface &of_interface,
                                    llmec::event::subscription &ev) {
    if (instance == 0) {
      instance = new Meter_manager(of_interface, ev);
    }
  }

Meter_manager* Meter_manager::get_instance(){
  assert(instance);
  return instance;
}


} // namespace meter_manager
} // namespace app
} // namespace llmec
