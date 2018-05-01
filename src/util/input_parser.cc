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
  \file input_parser.cc
  \brief parse the user inputs and present help
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/


#include <algorithm>

#include "input_parser.h"
#include "spdlog.h"

const std::string Input_parser::get_cmd_option(const std::string &option) const
{
  std::vector<std::string>::const_iterator itr;
  itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
  if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
    return *itr;
  }
  static const std::string empty_string("");
  return empty_string;
}

bool Input_parser::cmd_option_exists(const std::string &option) const
{
  return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}

void Input_parser::print_help() {
  spdlog::get("ll-mec")->info("Low Latency MEC platform");
  spdlog::get("ll-mec")->info("-h");
  spdlog::get("ll-mec")->info("");
  spdlog::get("ll-mec")->info("\tThis help");
  spdlog::get("ll-mec")->info("");
  spdlog::get("ll-mec")->info("-c [CONFIG_PATH]");
  spdlog::get("ll-mec")->info("");
  spdlog::get("ll-mec")->info("\tLoad config file from [CONFIG_PATH]. Default config will loaded if not specified");
}
