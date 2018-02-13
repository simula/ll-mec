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

#ifndef __BASIC_SWITCH_H__
#define __BASIC_SWITCH_H__
#include <unordered_set>
#include "app.h"

namespace llmec {
namespace app {
namespace switch_manager {

class Switch_manager : public llmec::app::App {
  public:
    Switch_manager(llmec::core::eps::OFInterface &of_interface) : llmec::app::App(of_interface) {}
    void event_callback(llmec::core::eps::ControllerEvent* ev);
    void start() override;
};

} // namespace basic_switch
} // namespace app
} // namespace llmec
#endif
