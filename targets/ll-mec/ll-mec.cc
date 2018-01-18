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

#define DEFAULT_CONFIG "llmec_config.json"

int main(int argc, char **argv){
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
    }
  }
  llmec_config->parse_config();
  llmec::core::eps::Controller ctrl("0.0.0.0", 6653, 4);

  //OpenFlow driver interface init
  llmec::core::eps::OFInterface of_interface;

  //TODO Application manager and low latency scheduler
  //Initialize application
  //SGWC sgwc(of_interface);
  //llmec::app::basic_switch::Basic_switch swt(of_interface);
  auto basic_switch = std::make_shared<llmec::app::basic_switch::Basic_switch>(of_interface);
  auto stats_manager = std::make_shared<llmec::app::stats::Stats_manager>(of_interface, ctrl);
  // TODO Need to handle this better (connection id)
  auto ue_manager = std::make_shared<llmec::app::uplane::Ue_manager>(of_interface, ctrl);

  //Register event for application
  //ctrl.register_for_event(&sgwc, EVENT_PACKET_IN);
  ctrl.register_for_event(basic_switch, llmec::core::eps::EVENT_SWITCH_UP);
  ctrl.register_for_event(stats_manager, llmec::core::eps::EVENT_MULTIPART_REPLY);
  //ctrl.register_for_event(stats_manager, llmec::core::eps::EVENT_SWITCH_UP);

  //std::thread sgwc_app(&SGWC::run, &sgwc);
  //std::thread swt_app(&llmec::app::basic_switch::Basic_switch::run, basic_switch);
  std::thread stats_manager_app(&llmec::app::stats::Stats_manager::run, stats_manager);

  //northbound api initial
  Pistache::Port port(9999);
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
  ctrl.start(true);

  //wait_for_sigint();
  //ctrl.stop();
  return 0;
}
