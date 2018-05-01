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
  \file rest_manager.h
  \brief manages the rest interface in terms of init, start, register, and shutdown
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#ifndef __REST_MANAGER_H_
#define __REST_MANAGER_H_

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "rest_calls.h"

namespace llmec {
namespace north_api {

class Rest_manager {
  public:
    Rest_manager(Pistache::Address address) : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(address)) { }
    void init(size_t thr = 1);
    void start();
    void shutdown();
    void register_calls(llmec::north_api::Rest_calls& calls);

  private:
    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router router_;
};

} // namespace north_api
} // namespace llmec

#endif
