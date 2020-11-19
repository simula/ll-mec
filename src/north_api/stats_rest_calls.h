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
  \file stats_rest_calls.h
  \brief public UE stats rest calls
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#ifndef __STATS_REST_CALLS_H__
#define __STATS_REST_CALLS_H__

#include <pistache/http.h>
//undefine macro UNUSED of pistache to avoid warnings
#undef UNUSED

#include "rest_calls.h"
#include "stats_manager.h"

namespace llmec {
namespace north_api {

class Stats_rest_calls : public Rest_calls {
  public:
    Stats_rest_calls(std::shared_ptr<llmec::app::stats::Stats_manager> stats_manager) : stats_manager(stats_manager) { }
    void register_calls(Pistache::Rest::Router& router);
    void get_flow_stats(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_flow_stats_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_flow_stats_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
  private:
    std::shared_ptr<llmec::app::stats::Stats_manager> stats_manager;
};

} // namespace north_api
} // namespace llmec


#endif

