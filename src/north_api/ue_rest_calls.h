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
  \file ue_rest_calls.h
  \brief public UE rest calls
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#ifndef __UE_REST_CALLS_H__
#define __UE_REST_CALLS_H__

#include <pistache/http.h>

#include "rest_calls.h"
#include "ue_manager.h"

namespace llmec {
namespace north_api {

class Ue_rest_calls : public Rest_calls {
  public:
    Ue_rest_calls() { }
    void register_calls(Pistache::Rest::Router& router);
    void add_bearer(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_bearer_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_bearer_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_bearer_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void add_redirect_bearer_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void add_redirect_bearer_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void delete_redirect_bearer_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void delete_redirect_bearer_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void delete_bearer_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void delete_bearer_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void delete_bearer_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_slice_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_slice_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};

} // namespace north_api
} // namespace llmec


#endif

