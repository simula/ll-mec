/*
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
  \file
  \brief
  \author
  \company
  \email:
*/

#include <iostream>
#include <thread>
#include <memory>
#include <pistache/endpoint.h>
#include <unistd.h>

#include "controller.h"
#include "sgwc.h"
#include "switch_manager.h"
#include "stats_manager.h"
#include "ue_manager.h"
#include "of_interface.h"
#include "controller_event.h"
#include "rest_manager.h"
#include "stats_rest_calls.h"
#include "ue_rest_calls.h"
#include "context_manager.h"
#include "input_parser.h"
#include "conf.h"
#include "spdlog.h"
#include "mp1-api-server.h"
//#include "mp2-api-server.h" //Mp2ManagementAPI
#include "rib.h"
#include "rib_updater.h"

#define DEFAULT_CONFIG "llmec_config.json"
#define LOG_NAME "ll-mec"
using namespace llmec::mp1::api;
using namespace llmec::mp1::rib;
int main(int argc, char **argv){
  /* Initialize logger*/
  auto console = spdlog::stdout_color_mt(LOG_NAME);
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");


  /* initialize command arguments parser*/
  Input_parser input(argc, argv);
  Conf* llmec_config = Conf::getInstance();
  llmec_config->config_path = DEFAULT_CONFIG;

  /* Start parsing command line arguments */
  if (input.cmd_option_exists("-h")) {
    Input_parser::print_help();
    return 0;
  }
  /* Read the config file path*/
  else if (input.cmd_option_exists("-c")) {
    std::string config_path = input.get_cmd_option("-c");
    if (!config_path.empty()) {
      llmec_config->config_path = config_path;
      spdlog::get("ll-mec")->info("Configuration file {} loaded", config_path);
    }
    else {
      spdlog::get("ll-mec")->info("No configuration file specified. Default config path loaded");
    }
  }
  //Set log level
  if (input.cmd_option_exists("-l")){
	  std::string log_level = input.get_cmd_option("-l");
	  spdlog::set_level(spdlog::level::info);
	  if (log_level.compare("debug") == 0) spdlog::set_level(spdlog::level::debug);
	  if (log_level.compare("warn") == 0) spdlog::set_level(spdlog::level::warn);
	  if (log_level.compare("trace") == 0) spdlog::set_level(spdlog::level::trace);
  }

  llmec_config->parse_config();

  /* Initial the controller based on the config */
  llmec::core::eps::Controller::create_instance(llmec_config->X["llmec"]["address"].get<std::string>().c_str(), llmec_config->X["llmec"]["port"].get<int>(), llmec_config->X["llmec"]["number_of_workers"].get<int>(), llmec_config->X["llmec"]["secure_connection"].get<bool>());
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  llmec::data::Context_manager::create_instance();

  //OpenFlow driver interface init
  llmec::core::eps::OFInterface of_interface;

  //Initialize application
  auto switch_manager = std::make_shared<llmec::app::switch_manager::Switch_manager>(of_interface);
  auto stats_manager = std::make_shared<llmec::app::stats::Stats_manager>(of_interface);
  llmec::app::uplane::Ue_manager::create_instance(of_interface);
  llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
//  auto ue_manager = std::make_shared<llmec::app::uplane::Ue_manager>(of_interface);

  //Register event for application
  ctrl->register_for_event(switch_manager, llmec::core::eps::EVENT_SWITCH_UP);
  ctrl->register_for_event(stats_manager, llmec::core::eps::EVENT_MULTIPART_REPLY);

  std::thread stats_manager_app(&llmec::app::stats::Stats_manager::run, stats_manager);

   //northbound api initial
  Pistache::Port port(llmec_config->X["northbound_api"]["port"].get<int>());
  Pistache::Address addr(Pistache::Ipv4::any(), port);
  llmec::north_api::Rest_manager rest_manager(addr);

  //rest calls setup
  llmec::north_api::Stats_rest_calls stats_rest_calls(std::dynamic_pointer_cast<llmec::app::stats::Stats_manager>(stats_manager));
  llmec::north_api::Ue_rest_calls ue_rest_calls;

  //calls register
  rest_manager.register_calls(stats_rest_calls);
  rest_manager.register_calls(ue_rest_calls);

  rest_manager.init(1);
  std::thread rest_manager_app(&llmec::north_api::Rest_manager::start, rest_manager);

  //Mp1 API
  //get list of FlexRAN controllers
  nlohmann::json flexRAN =  llmec_config->X["flexran"];
  std::string mp1ApiMode = ((llmec_config->X["mp1_api"])["mode"]).get<std::string>().c_str();

  int numControllers = flexRAN.size();
  std::vector<std::pair<std::string, int>> flexRANControllers;
  for (int i=0; i <numControllers; i++ ){
	  std::pair<std::string, int> controller = std::make_pair((flexRAN.at(i))["address"].get<std::string>().c_str(), (flexRAN.at(i))["port"].get<int>());
	  flexRANControllers.push_back(controller);
  }
  Pistache::Address addr_mp1(Pistache::Ipv4::any(), Pistache::Port(llmec_config->X["mp1_api"]["port"].get<int>()));
  // Create the rib
  llmec::mp1::rib::Rib rib;
  Mp1Manager mp1Manager(addr_mp1, rib);
  mp1Manager.init(2);
  //mp1Manager.start();
  //mp1Manager.shutdown();
  std::thread mp1_manager_app(&Mp1Manager::start, mp1Manager);



  struct itimerspec its;
  its.it_value.tv_sec = 10;
  its.it_value.tv_nsec = 0;//100 * 1000 * 1000; //100ms

  rib_updater ribUpdater(rib, its, flexRANControllers, mp1ApiMode);
  std::thread rib_updater(&rib_updater::run, ribUpdater);



  //start Mp2 API
 
  //Controller start
  ctrl->start(true);

  return 0;
}
