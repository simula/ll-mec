/* The MIT License (MIT)

   Copyright (c) 2018 Anta Huang (anta.huang@eurecom.fr)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include <iostream>
#include <thread>
#include <memory>
#include <pistache/endpoint.h>

#include "controller.h"
#include "sgwc.h"
#include "basic_switch.h"
#include "stats_manager.h"
#include "ue_manager.h"
#include "of_interface.h"
#include "controller_event.h"
#include "rest_manager.h"
#include "stats_rest_calls.h"
#include "ue_rest_calls.h"
#include "input_parser.h"
#include "conf.h"
#include "spdlog.h"

#define DEFAULT_CONFIG "llmec_config.json"
#define LOG_NAME "ll-mec"

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
  llmec_config->parse_config();

  /* Initial the controller based on the config */
  llmec::core::eps::Controller::create_instance(llmec_config->X["llmec"]["address"].get<std::string>().c_str(), llmec_config->X["llmec"]["port"].get<int>(), llmec_config->X["llmec"]["number_of_workers"].get<int>(), llmec_config->X["llmec"]["secure_connection"].get<bool>());
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();

  //OpenFlow driver interface init
  llmec::core::eps::OFInterface of_interface;

  //Initialize application
  auto basic_switch = std::make_shared<llmec::app::basic_switch::Basic_switch>(of_interface);
  auto stats_manager = std::make_shared<llmec::app::stats::Stats_manager>(of_interface);
  auto ue_manager = std::make_shared<llmec::app::uplane::Ue_manager>(of_interface);

  //Register event for application
  ctrl->register_for_event(basic_switch, llmec::core::eps::EVENT_SWITCH_UP);
  ctrl->register_for_event(stats_manager, llmec::core::eps::EVENT_MULTIPART_REPLY);

  std::thread stats_manager_app(&llmec::app::stats::Stats_manager::run, stats_manager);

   //northbound api initial
  Pistache::Port port(llmec_config->X["northbound_api"]["port"].get<int>());
  Pistache::Address addr(Pistache::Ipv4::any(), port);
  llmec::north_api::Rest_manager rest_manager(addr);

  //rest calls setup
  llmec::north_api::Stats_rest_calls stats_rest_calls(std::dynamic_pointer_cast<llmec::app::stats::Stats_manager>(stats_manager));
  llmec::north_api::Ue_rest_calls ue_rest_calls(std::dynamic_pointer_cast<llmec::app::uplane::Ue_manager>(ue_manager));

  //calls register
  rest_manager.register_calls(stats_rest_calls);
  rest_manager.register_calls(ue_rest_calls);

  rest_manager.init(1);
  std::thread rest_manager_app(&llmec::north_api::Rest_manager::start, rest_manager);

  //Controller start
  ctrl->start(true);

  return 0;
}
