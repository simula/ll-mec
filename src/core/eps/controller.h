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

#include "app.h"

namespace llmec {
namespace core {
namespace eps {

class Controller : public fluid_base::OFServer {
  public:
    static Controller* get_instance();
    static void create_instance(const char* address, const int port, const int n_workers, bool secure);
    std::unordered_map<int, std::vector<std::shared_ptr<llmec::app::App>> > event_listeners_;
    // TODO Need to be refactor for multiple switch
    // Assume only one switch for now
    int conn_id;
    // Non-lock map for now
    bool running_;

    virtual void connection_callback(fluid_base::OFConnection* of_conn, fluid_base::OFConnection::Event type);
    virtual void message_callback(fluid_base::OFConnection* of_conn, uint8_t type, void* data, size_t len);
    void register_for_event(const std::shared_ptr<llmec::app::App>& app, int event_type);

    void stop();

    inline void dispatch_event(ControllerEvent* ev) {
      if (not this->running_) {
        delete ev;
        return;
      }
      for (auto app : event_listeners_[ev->get_type()]) {
        app->event_callback(ev);
      }
      delete ev;

    }
  private:
    static Controller* instance;
    Controller(
        const char* address = "0.0.0.0",
        const int port = 6653,
        const int n_workers = 4,
        bool secure = false):
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
