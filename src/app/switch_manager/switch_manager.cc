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
#include "switch_manager.h"
#include "spdlog.h"
#include "context_manager.h"

namespace llmec {
namespace app {
namespace switch_manager {

void Switch_manager::event_callback(llmec::core::eps::ControllerEvent* ev) {
  llmec::data::Context_manager* context_manager = llmec::data::Context_manager::get_instance();
  if (ev->get_type() == llmec::core::eps::EVENT_SWITCH_UP) {
    this->of_interface.install_default_flow(ev->of_conn_);
    spdlog::get("ll-mec")->info("Switch id={} installed default flow", ev->of_conn_->get_id());
    //switch_set_.insert(ev->of_conn_->get_id());
    context_manager->add_switch(ev->of_conn_->get_id());
  }
  if (ev->get_type() == llmec::core::eps::EVENT_SWITCH_DOWN) {
    /* the switch id, mec id are not related together for the moment */
    //this->of_interface.flush_flow(ev->of_conn_->get_id());
    spdlog::get("ll-mec")->info("Switch id={} flushed flow", ev->of_conn_->get_id());
    //switch_set_.insert(ev->of_conn_->get_id());
    context_manager->delete_switch(ev->of_conn_->get_id());
  }
}
void Switch_manager::start() {
  while(true){
    //std::cout<<"Switch"<<std::endl;
  }
}

} // namespace basic_switch
} // namespace app
} // namespace llmec
