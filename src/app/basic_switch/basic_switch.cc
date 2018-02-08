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
#include "basic_switch.h"
#include "spdlog.h"

namespace llmec {
namespace app {
namespace basic_switch {

void Basic_switch::event_callback(llmec::core::eps::ControllerEvent* ev) {
  if (ev->get_type() == llmec::core::eps::EVENT_SWITCH_UP) {
    this->of_interface.install_default_flow(ev->of_conn_);
    spdlog::get("ll-mec")->info("Switch id={} installed default flow", ev->of_conn_->get_id());
    switch_set_.insert(ev->of_conn_->get_id());
  }
}
std::unordered_set<int> Basic_switch::get_switch_list() {
  return this->switch_set_;
}
void Basic_switch::start() {
  while(true){
    //std::cout<<"Switch"<<std::endl;
  }
}

} // namespace basic_switch
} // namespace app
} // namespace llmec
