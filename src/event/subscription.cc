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

/*! \file    subscription.cc
 *  \brief   Event subscription: callback subscription for certain events
 *  \authors Robert Schmidt
 *  \company Eurecom
 *  \email   robert.schmidt@eurecom.fr
 */

#include "subscription.h"
#include <algorithm>

namespace llmec {
namespace event {

bs2::connection subscription::subscribe_openflow_switch_up(
      const openflow_cb<llmec::core::eps::SwitchUpEvent>::slot_type& cb) {
  return of_switch_up.connect(cb);
}

bs2::connection subscription::subscribe_openflow_switch_down(
      const openflow_cb<llmec::core::eps::SwitchDownEvent>::slot_type& cb) {
  return of_switch_down.connect(cb);
}

bs2::connection subscription::subscribe_openflow_packet_in(
    const openflow_cb<llmec::core::eps::PacketInEvent>::slot_type& cb) {
  return of_packet_in.connect(cb);
}

bs2::connection subscription::subscribe_openflow_multipart_reply(
    const openflow_cb<llmec::core::eps::MultipartReplyEvent>::slot_type& cb) {
  return of_multipart_reply.connect(cb);
}

bs2::connection subscription::subscribe_openflow_meter_mod(
    const openflow_cb<llmec::core::eps::MeterEvent>::slot_type& cb) {
  return of_meter_mod.connect(cb);
}

bs2::connection subscription::subscribe_ue_rab_establishment(
    const rab_cb::slot_type& cb) {
  return ue_rab_establishment.connect(cb);
};

} // namespace event
} // namespace llmec
