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
  \file conroller.h
  \brief OF controller class definition 
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// #include <boost/unordered_map.hpp>
#include <unordered_map>
#include <string.h>
#include <list>
#include <signal.h>
#include <unistd.h>
#include <memory>

#include <fluid/OFServer.hh>
//undefine macro UNUSED of pistache to avoid warnings
#undef UNUSED

#include "app.h"
#include "subscription.h"

namespace llmec {
namespace core {
namespace eps {

class Controller : public fluid_base::OFServer {
  public:
    static Controller* get_instance();
    static void create_instance(llmec::event::subscription& ev, const char* address, const int port, const int n_workers, bool secure);
    std::unordered_map<int, std::vector<std::shared_ptr<llmec::app::App>> > event_listeners_;
    // TODO Need to be refactor for multiple switch
    // Assume only one switch for now
    int conn_id;
    // Non-lock map for now
    bool running_;

    virtual void connection_callback(fluid_base::OFConnection* of_conn, fluid_base::OFConnection::Event type);
    virtual void message_callback(fluid_base::OFConnection* of_conn, uint8_t type, void* data, size_t len);

    void stop();

  private:
    static Controller* instance;
    llmec::event::subscription& event_sub;
    Controller(
        llmec::event::subscription& ev,
        const char* address = "0.0.0.0",
        const int port = 6653,
        const int n_workers = 4,
        bool secure = false):
      event_sub(ev),
      fluid_base::OFServer(
          address,
          port,
          n_workers,
          secure,
          fluid_base::OFServerSettings().supported_version(1).supported_version(4).keep_data_ownership(false)) {
        this->running_ = true;
      }
};

} // namespace eps
} // namespace core
} // namespace llmec
#endif
