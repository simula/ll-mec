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

#include "rest_manager.h"

namespace llmec {
namespace north_api {

void Rest_manager::init(size_t thr) {
  auto opts = Pistache::Http::Endpoint::options().threads(thr);
  httpEndpoint->init(opts);
}

void Rest_manager::start() {
  httpEndpoint->setHandler(router_.handler());
  httpEndpoint->serve();
}

void Rest_manager::shutdown() {
  httpEndpoint->shutdown();
}

void Rest_manager::register_calls(llmec::north_api::Rest_calls& calls) {
  calls.register_calls(router_);
}

} // namespace north_api
} // namespace llmec
