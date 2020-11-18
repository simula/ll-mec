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
#include "conf.h"
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

bool Ue_manager::add_bearer(json context){
  spdlog::get("ll-mec")->debug("Ue_manager add bearer {}", context.dump());
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  Conf* llmec_config = Conf::getInstance();
  bool support_meter = llmec_config->X["ovs_switch"]["support_meter"].get<bool>();

  uint64_t id = context_manager->get_id(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>());
  uint32_t meter_id = DEFAULT_MT_ID ;//default MT id
  uint32_t meter_rate = 1000000; //default meter rate
  uint32_t meter_burst_size = 50000; //default burst_size

  if (support_meter) {
    uint64_t slice_id = context["slice_id"].get<int>();
    if ((slice_id > 0) && (slice_id <= 16)){ //MT for slice (id = 1-16)
      meter_id = (uint32_t) (slice_id);
      if (context.count("meter_rate") != 0) meter_rate = context["meter_rate"].get<int>();
      if (context.count("burst_size") != 0) meter_burst_size = context["burst_size"].get<int>();
    } else { //if MT information is available-> create a new UE-specified MT, else use default MT
      if ((context.count("meter_rate") != 0) | (context.count("burst_size") != 0))
        meter_id = context_manager->next_meter_id();
      else
        meter_id = DEFAULT_MT_ID;
      if (context.count("meter_rate") != 0) meter_rate = context["meter_rate"].get<int>();
      if (context.count("burst_size") != 0) meter_burst_size = context["burst_size"].get<int>();
    }

    context["meter_id"] = meter_id;
    //store meter's info
    context_manager->add_meter(meter_id, meter_rate, meter_burst_size);
  }

  //Bearer already exists. Remove it and then add (Overwrite)
  if (id != 0) {
    //context_manager->delete_bearer(id);
    for (auto each:context_manager->get_switch_set()) {
      fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
      if (of_conn_ == nullptr || !of_conn_->is_alive())
        continue;
      this->of_interface.flush_flow(of_conn_, id);
    }
    //update bearer's info
    context_manager->add_bearer(id, context);
    spdlog::get("ll-mec")->info("Overwrite UE bearer {}: {}", id, context.dump());
    if (support_meter)
      spdlog::get("ll-mec")->info("UE bearer {} is using the meter: {}", id, meter_id);
  }
  else {
	//add bearer's info
	context_manager->add_bearer(context);
	id = context_manager->get_id(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>());
    spdlog::get("ll-mec")->info("Add UE bearer {}: {}", id, context.dump());
    if (support_meter)
      spdlog::get("ll-mec")->info("UE bearer {} is using the meter: {}", id, meter_id);
  }

  if (support_meter) {
    //install new MT
    if (meter_id != DEFAULT_MT_ID){
      for (auto each:context_manager->get_switch_set()) {
        fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
        if (of_conn_ == nullptr || !of_conn_->is_alive())
          continue;
        // this->of_interface.install_default_meter_drop(of_conn_,meter_id);
        this->of_interface.install_meter_mod_drop(of_conn_, meter_id, meter_rate, meter_burst_size);
      }
    }
  }

  Metadata metadata;
  if (!context["tos"].empty()) {
    metadata.ipdscp = (uint8_t)((context["tos"].get<int>() & 0xFC) >> 2);
    metadata.ipecn = (uint8_t) context["tos"].get<int>() & 0x3;
  }

  //associate flow with the created MT
  for (auto each:context_manager->get_switch_set()) {
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
    if (of_conn_ == nullptr || !of_conn_->is_alive())
      continue;
    if (support_meter) {
      this->of_interface.install_default_meter_UE_ul_flow(of_conn_, id, meter_id, context["s1_ul_teid"].get<int>(), metadata);
      this->of_interface.install_default_meter_UE_dl_flow(of_conn_, id, meter_id, context["ue_ip"].get<std::string>(), context["s1_dl_teid"].get<int>(), context["enb_ip"].get<std::string>(), metadata);

    } else {
      this->of_interface.install_default_UE_ul_flow(of_conn_, id, context["s1_ul_teid"].get<int>(), metadata);
      this->of_interface.install_default_UE_dl_flow(of_conn_, id, context["ue_ip"].get<std::string>(), context["s1_dl_teid"].get<int>(), context["enb_ip"].get<std::string>(), metadata);

    }
  }

  //notify the event for Mp1 API
  dispatch_event(context["imsi"].get<std::string>(), UE_EVENT_RAB_ESTABLISHMENT);
  dispatch_event(context["imsi"].get<std::string>(), UE_EVENT_S1_BEARER);
  return true;
}

/*
 *
 *
bool Ue_manager::modify_meter(json context){
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  uint32_t meterid = context_manager->get_meterid(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>(),context["slice_id"].get<int>()); //get the eps_meter_id value from the json file
  this->of_interface.install_meter_mod(of_conn_, context["meter_command"].get<std::string>(), context["meter_flags"].get<std::string>(), context["eps_meter_id"].get<int>(), context["meter_type"].get<std::string>(), context["meter_rate"].get<int>(), context["meter_burst_size"].get<int>(), context["meter_prec_level"].get<int>(),context["meter_experimenter"].get<int>() );
}
*/

bool Ue_manager::add_redirect_bearer(uint64_t id, uint32_t meter_id, json context) {
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  Conf* llmec_config = Conf::getInstance();
  bool support_meter = llmec_config->X["ovs_switch"]["support_meter"].get<bool>();

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
	  if (support_meter) {
	    this->of_interface.redirect_edge_service_ul_meter_flow(of_conn_, id, meter_id, bearer["s1_ul_teid"].get<int>(), context["from"].get<std::string>(), context["to"].get<std::string>(), metadata);
	    this->of_interface.redirect_edge_service_dl_meter_flow(of_conn_, id, meter_id, bearer["ue_ip"].get<std::string>(), bearer["s1_dl_teid"].get<int>(), bearer["enb_ip"].get<std::string>(), context["from"].get<std::string>(), context["to"].get<std::string>(), metadata);
	  } else {
	    this->of_interface.redirect_edge_service_ul_flow(of_conn_, id, bearer["s1_ul_teid"].get<int>(), context["from"].get<std::string>(), context["to"].get<std::string>(), metadata);
	    this->of_interface.redirect_edge_service_dl_flow(of_conn_, id, bearer["ue_ip"].get<std::string>(), bearer["s1_dl_teid"].get<int>(), bearer["enb_ip"].get<std::string>(), context["from"].get<std::string>(), context["to"].get<std::string>(), metadata);
	  }
}
  spdlog::get("ll-mec")->info("Redirect bearer id={} from {} to {}", id, context["from"].get<std::string>(), context["to"].get<std::string>());
  return true;
}

bool Ue_manager::delete_redirect_bearer(uint64_t id) {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  Conf* llmec_config = Conf::getInstance();
  bool support_meter = llmec_config->X["ovs_switch"]["support_meter"].get<bool>();

  /* No such ue context */
  if (context_manager->id_exist(id) == false)
    return false;

  json bearer = context_manager->get_bearer_context(id);
  for (auto each:context_manager->get_switch_set()) {
    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
    if (of_conn_ == nullptr || !of_conn_->is_alive())
      continue;
    this->of_interface.flush_flow(of_conn_, id);
//    this->of_interface.flush_meter(of_conn_, meterid); //meterid
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
    if (support_meter){
      this->of_interface.install_default_meter_UE_ul_flow(of_conn_, id, DEFAULT_MT_ID, bearer["s1_ul_teid"].get<int>(), metadata);
      this->of_interface.install_default_meter_UE_dl_flow(of_conn_, id, DEFAULT_MT_ID, bearer["ue_ip"].get<std::string>(), bearer["s1_dl_teid"].get<int>(), bearer["enb_ip"].get<std::string>(), metadata);
    } else {
      this->of_interface.install_default_UE_ul_flow(of_conn_, id, bearer["s1_ul_teid"].get<int>(), metadata);
      this->of_interface.install_default_UE_dl_flow(of_conn_, id, bearer["ue_ip"].get<std::string>(), bearer["s1_dl_teid"].get<int>(), bearer["enb_ip"].get<std::string>(), metadata);
    }
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

/*
 * Remove the meter tables
 *
 */
bool Ue_manager::delete_meter_table(uint32_t meter_id){
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  /* flush meter*/
  std::vector<uint64_t> id_list = context_manager->get_id_list();
  for (auto id : id_list) {
	  for (auto switch_id:context_manager->get_switch_set()) {
		  fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(switch_id);
		  if (of_conn_ == nullptr || !of_conn_->is_alive())
			  continue;
		  this->of_interface.flush_meter(of_conn_, meter_id);
	  }
  }

  //context_manager->clean();
  //remove meter table from context manager
  context_manager->delete_meter(meter_id);

  //Move the flows associated to this meter table to the default MT
  for (auto id : id_list) {
	  json bearer_context = context_manager->get_bearer_context(id);
	  if (meter_id == bearer_context["meter_id"].get<int>()){
		  spdlog::get("ll-mec")->info("[Ue_manager] delete_meter_table, associate flow {} from meter {} to the default MT {}", id, meter_id, DEFAULT_MT_ID);
		  //update the context with default meter id
		  bearer_context["meter_id"] = DEFAULT_MT_ID;
		  context_manager->add_bearer(id, bearer_context);
		  //associate this flow to the default table
		  Metadata metadata;
		  if (!bearer_context["tos"].empty()) {
		    metadata.ipdscp = (uint8_t)((bearer_context["tos"].get<int>() & 0xFC) >> 2);
		    metadata.ipecn = (uint8_t) bearer_context["tos"].get<int>() & 0x3;
		  }

		  for (auto each:context_manager->get_switch_set()) {
		    fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
		    if (of_conn_ == nullptr || !of_conn_->is_alive())
		      continue;
		    this->of_interface.install_default_meter_UE_ul_flow(of_conn_, id, DEFAULT_MT_ID, bearer_context["s1_ul_teid"].get<int>(), metadata);
		    this->of_interface.install_default_meter_UE_dl_flow(of_conn_, id, DEFAULT_MT_ID, bearer_context["ue_ip"].get<std::string>(), bearer_context["s1_dl_teid"].get<int>(), bearer_context["enb_ip"].get<std::string>(), metadata);
		  }
	  }
  }

  spdlog::get("ll-mec")->info("Removed the Meter {}!", meter_id);
  return true;
}

/*
 * Update the meter tables
 *
 */
bool Ue_manager::update_meter_table(uint32_t meter_id,  uint32_t meter_rate,  uint32_t meter_burst_size){
	llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
	llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
	//update MT info
	context_manager->add_meter(meter_id, meter_rate, meter_burst_size);

	//update MT
	for (auto each:context_manager->get_switch_set()) {
		fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(each);
		if (of_conn_ == nullptr || !of_conn_->is_alive())
			continue;
		this->of_interface.modify_meter_mod_drop(of_conn_, meter_id, meter_rate, meter_burst_size);
	}


	spdlog::get("ll-mec")->info("Updated Meter id {}!", meter_id);
	return true;
}

/*
 * Remove all the bearers
 */
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
//      this->of_interface.flush_meter(of_conn_,meterid);
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
/*
//retrive the meterid
uint32_t Ue_manager::get_meterid( uint32_t eps_meter_id){
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  uint32_t meterid = context_manager->get_meterid(eps_meter_id);
  return meterid;
}*/

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

void Ue_manager::register_for_event(const std::shared_ptr<llmec::mp1::api::Mp1Api>& apiApp, int event_type) {
  ue_event_listeners_[event_type].push_back(apiApp);
}

} // namespace uplane
} // namespace app
} // namespace llmec
