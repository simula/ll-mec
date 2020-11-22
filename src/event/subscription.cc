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

bs2::connection subscription::subscribe_ue_cell_change(
    const ue_cb::slot_type& cb) {
  return ue_cell_change.connect(cb);
}

bs2::connection subscription::subscribe_ue_rab_establishment(
    const rab_cb::slot_type& cb) {
  return ue_rab_establishment.connect(cb);
};

bs2::connection subscription::subscribe_ue_rab_modification(
    const rab_cb::slot_type& cb) {
  return ue_rab_modification.connect(cb);
};

bs2::connection subscription::subscribe_ue_rab_release(
    const rab_cb::slot_type& cb) {
  return ue_rab_release.connect(cb);
};

bs2::connection subscription::subscribe_ue_meas_report_ue(
    const ue_cb::slot_type& cb) {
  return ue_meas_report_ue.connect(cb);
}

bs2::connection subscription::subscribe_ue_meas_timing_advance(
    const ue_cb::slot_type& cb) {
  return ue_meas_timing_advance.connect(cb);
}

bs2::connection subscription::subscribe_ue_ca_reconf(
    const cc_cb::slot_type& cb) {
  return ue_ca_reconf.connect(cb);
}

bs2::connection subscription::subscribe_ue_s1_bearer(
    const s1_cb::slot_type& cb) {
  return ue_s1_bearer.connect(cb);
}

bs2::connection subscription::subscribe_mp1_service_availability(
    const mp1_sub_cb::slot_type& cb) {
  return mp1_service_availability.connect(cb);
}

bs2::connection subscription::subscribe_mp1_application_termination(
    const mp1_sub_cb::slot_type& cb) {
  return mp1_application_termination.connect(cb);
}

bs2::connection subscription::subscribe_ue_rab_redirect_add(
    const rab_redir_cb::slot_type& cb) {
  return ue_rab_redir_add.connect(cb);
}

bs2::connection subscription::subscribe_ue_rab_redirect_modify(
    const rab_redir_cb::slot_type& cb) {
  return ue_rab_redir_modif.connect(cb);
}

bs2::connection subscription::subscribe_ue_rab_redirect_delete(
    const rab_cb::slot_type& cb) {
  return ue_rab_redir_del.connect(cb);
}

bs2::connection subscription::subscribe_meter_update(
    const meter_cb::slot_type& cb) {
  return meter_update.connect(cb);
}

bs2::connection subscription::subscribe_meter_delete(
    const meter_cb::slot_type& cb) {
  return meter_delete.connect(cb);
}

bs2::connection subscription::subscribe_task_tick(
    const task_cb::slot_type& cb, uint64_t period, uint64_t start) {
  /* Wrap the actual callback in a lambda. The latter checks whether the
   * current time is after start time, and ensures that the callback is only
   * called every X ms with X being the period time. This way, it is possible
   * to register to be notified every X ms instead of every ms, which provides
   * greater freedom to implementations. */
  auto f = [period,start,cb] (uint64_t t)
           {
             if (t >= start && (t - start) % period == 0) cb(t);
           };
  return task_tick.connect(f);
}

} // namespace event
} // namespace llmec
