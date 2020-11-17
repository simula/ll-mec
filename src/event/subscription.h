/*
 * Copyright 2016-2020 Eurecom and Mosaic5G Platforms Authors
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

/*! \file    subscription.h
 *  \brief   Event subscription: callback subscription for certain events
 *  \authors Robert Schmidt
 *  \company Eurecom
 *  \email   robert.schmidt@eurecom.fr
 */

#ifndef __SUBSCRIPTION_H__
#define __SUBSCRIPTION_H__

#include <atomic>
#include <boost/signals2.hpp>
namespace bs2 = boost::signals2;

#include "callbacks.h"

namespace llmec {
  namespace core {
    namespace eps {
      class Controller;
    }
  }
}

namespace llmec {
namespace event {

class subscription {
  public:
    // friend classes can access private fields
    friend class llmec::core::eps::Controller;

    subscription() {}

    bs2::connection subscribe_openflow_switch_up(
        const openflow_cb<llmec::core::eps::SwitchUpEvent>::slot_type& cb);
    bs2::connection subscribe_openflow_switch_down(
        const openflow_cb<llmec::core::eps::SwitchDownEvent>::slot_type& cb);

  private:
    openflow_cb<llmec::core::eps::SwitchUpEvent> of_switch_up;
    openflow_cb<llmec::core::eps::SwitchDownEvent> of_switch_down;
};

} // namespace llmec
} // namespace event

#endif /* __SUBSCRIPTION_H__ */
