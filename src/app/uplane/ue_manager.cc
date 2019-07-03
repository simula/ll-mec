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
  \file ue_manager.cc
  \brief managing the users and bearers, and their associations to different slices 
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#include <iostream>

#include "ue_manager.h"
#include "context_manager.h"
#include "spdlog.h"
#include "metadata.h"

namespace llmec {
namespace app {
namespace uplane {

void Ue_manager::event_callback(llmec::core::eps::ControllerEvent* ev)
{
}

void Ue_manager::start()
{
/*  while(true){
  }*/
}

bool Ue_manager::add_bearer(json context)
{
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();

  uint64_t id = context_manager->get_id(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>());

  spdlog::get("ll-mec")->debug("bearer {}", id);
  /* Bearer already exists. Remove it and then add (Overwrite) */
  if (id != 0) {
    context_manager->delete_bearer(id);
    for (auto each:context_manager->get_switch_set()) {
      fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
      if (of_conn_ == nullptr || !of_conn_->is_alive())
        continue;
      this->of_interface.flush_flow(of_conn_, id);
    }
    context_manager->add_bearer(id, context);
    spdlog::get("ll-mec")->info("Overwrite UE bearer {}: {}", id, context.dump());
  }
  else {
    context_manager->add_bearer(context);
    id = context_manager->get_id(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>());
    spdlog::get("ll-mec")->info("Add UE bearer {}: {}", id, context.dump());
  }

  Metadata metadata;
  if (!context["tos"].empty()) {
    metadata.ipdscp = (uint8_t)((context["tos"].get<int>() & 0xFC) >> 2);
    metadata.ipecn = (uint8_t) context["tos"].get<int>() & 0x3;
  }

  
  for (auto each:context_manager->get_switch_set()) {
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
    if (of_conn_ == nullptr || !of_conn_->is_alive())
      continue;
    this->of_interface.install_default_UE_ul_flow(of_conn_, id, context["s1_ul_teid"].get<int>(), metadata);
    this->of_interface.install_default_UE_dl_flow(of_conn_, id, context["ue_ip"].get<std::string>(), context["s1_dl_teid"].get<int>(), context["enb_ip"].get<std::string>(), metadata);
  }

  //notify the event for Mp1 API
  dispatch_event(UE_EVENT_RAB_ESTABLISHMENT);
  dispatch_event(UE_EVENT_S1_BEARER);
  return true;
}

bool Ue_manager::add_redirect_bearer(uint64_t id, json context) {
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();

  /* No such ue context */
  if (context_manager->id_exist(id) == false)
    return false;

  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();

  /* Add redirect information in database */
  context_manager->add_redirect_bearer(id, context);
  json bearer = context_manager->get_bearer_context(id);

  Metadata metadata;
  if (!context["tos"].empty()) {
    metadata.ipdscp = (uint8_t)((context["tos"].get<int>() & 0xFC) >> 2);
    metadata.ipecn = (uint8_t) context["tos"].get<int>() & 0x3;
  }
  for (auto each:context_manager->get_switch_set()) {
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
    if (of_conn_ == nullptr || !of_conn_->is_alive())
      continue;
    this->of_interface.redirect_edge_service_ul_flow(of_conn_, id, bearer["s1_ul_teid"].get<int>(), context["from"].get<std::string>(), context["to"].get<std::string>(), metadata);
    this->of_interface.redirect_edge_service_dl_flow(of_conn_, id, bearer["ue_ip"].get<std::string>(), bearer["s1_dl_teid"].get<int>(), bearer["enb_ip"].get<std::string>(), context["from"].get<std::string>(), context["to"].get<std::string>(), metadata);
  }

  spdlog::get("ll-mec")->info("Redirect bearer id={} from {} to {}", id, context["from"].get<std::string>(), context["to"].get<std::string>());
  return true;
}

bool Ue_manager::delete_redirect_bearer(uint64_t id) {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();

  /* No such ue context */
  if (context_manager->id_exist(id) == false)
    return false;

  json bearer = context_manager->get_bearer_context(id);
  for (auto each:context_manager->get_switch_set()) {
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
    if (of_conn_ == nullptr || !of_conn_->is_alive())
      continue;
    this->of_interface.flush_flow(of_conn_, id);
  }
  Metadata metadata;
  if (!bearer["tos"].empty()) {
    metadata.ipdscp = (bearer["tos"].get<uint8_t>() & 0xFC) >> 2;
    metadata.ipecn = bearer["tos"].get<uint8_t>() & 0x3;
  }
  for (auto each:context_manager->get_switch_set()) {
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
    if (of_conn_ == nullptr || !of_conn_->is_alive())
      continue;
    this->of_interface.install_default_UE_ul_flow(of_conn_, id, bearer["s1_ul_teid"].get<int>(), metadata);
    this->of_interface.install_default_UE_dl_flow(of_conn_, id, bearer["ue_ip"].get<std::string>(), bearer["s1_dl_teid"].get<int>(), bearer["enb_ip"].get<std::string>(), metadata);
  }

  /* Remove redirect information in UE context */
  context_manager->delete_redirect_bearer(id);

  spdlog::get("ll-mec")->info("No redirected traffic for UE id={}", id);
  return true;
}

json Ue_manager::get_bearer(uint64_t id) {
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  json response = context_manager->get_bearer_context(id);
  return response;
}

json Ue_manager::get_bearer_all() {
  json response = json::array();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  std::vector<uint64_t> id_list = context_manager->get_id_list();
  for (auto each:id_list)
    response.push_back(context_manager->get_bearer_context(each));
  return response;
}

bool Ue_manager::delete_bearer(uint64_t id) {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();

  /* Remove the ue context */
  context_manager->delete_bearer(id);

  /* Flush the bearer */
  for (auto each:context_manager->get_switch_set()) {
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
    if (of_conn_ == nullptr || !of_conn_->is_alive())
      continue;
    this->of_interface.flush_flow(of_conn_, id);
  }

  spdlog::get("ll-mec")->info("Removed UE id={}", id);

  return true;
}

bool Ue_manager::delete_bearer_all() {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();

  /* flush flow for each ue and clear the map */
  std::vector<uint64_t> id_list = context_manager->get_id_list();
  for (auto id:id_list) {
    for (auto switch_id:context_manager->get_switch_set()) {
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(switch_id);
    if (of_conn_ == nullptr || !of_conn_->is_alive())
      continue;
      this->of_interface.flush_flow(of_conn_, id);
    }
  }
  context_manager->clean();

  spdlog::get("ll-mec")->info("Removed all bearers");
  return true;
}

json Ue_manager::get_slice(uint64_t id) {
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  json response = context_manager->get_slice_group(id);
  return response;
}

json Ue_manager::get_slice_all() {
  json response;
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  std::vector<uint64_t> slice_id_list = context_manager->get_slice_id_list();
  for (auto each:slice_id_list)
    response[std::to_string(each)] = context_manager->get_slice_group(each);

  return response;
}

std::vector<uint64_t> Ue_manager::get_bearer_id_list() {
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  std::vector<uint64_t> bearer_id_list = context_manager->get_id_list();
  return bearer_id_list;
}

uint64_t Ue_manager::get_id(std::string imsi, uint64_t eps_bearer_id) {
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  uint64_t id = context_manager->get_id(imsi, eps_bearer_id);
  return id;
}

bool Ue_manager::id_exist(uint64_t id) {
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  return context_manager->id_exist(id);
}

Ue_manager* Ue_manager::instance = 0;

void Ue_manager::create_instance(llmec::core::eps::OFInterface &of_interface)
  {
    if (instance == 0) {
      instance = new Ue_manager(of_interface);
    }
  }

Ue_manager* Ue_manager::get_instance()
{
  assert(instance);
  return instance;
}

void Ue_manager::register_for_event(const std::shared_ptr<llmec::mp1::api::DefaultApi>& apiApp, int event_type) {
  ue_event_listeners_[event_type].push_back(apiApp);
}


} // namespace uplane
} // namespace app
} // namespace llmec
