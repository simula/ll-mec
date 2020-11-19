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

/*! \file    callbacks.h
 *  \brief   Callback definitions for controller events
 *  \authors Robert Schmidt
 *  \company Eurecom
 *  \email   robert.schmidt@eurecom.fr
 */

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <boost/signals2.hpp>
namespace bs2 = boost::signals2;

#include "controller_event.h"

namespace llmec {
namespace event {

    /// Single-thread callback for arbitrary OpenFlow message
    /// Argument is BS ID and the actual message
    template <typename ControllerEvent>
    using openflow_cb = typename bs2::signal_type<void(ControllerEvent),
        bs2::keywords::mutex_type<bs2::dummy_mutex>>::type;

    /// Single-thread callback for BS-IMSI-RAB type event
    /// Argument is BS IP addr, IMSI of UE, and RAB bearer ID
    typedef bs2::signal_type<void(std::string, std::string, int),
        bs2::keywords::mutex_type<bs2::dummy_mutex>>::type rab_cb;

    /// Single-thread callback for BS-IMSI type event
    /// Argument is BS IP addr and IMSI of UE
    typedef bs2::signal_type<void(std::string, std::string),
        bs2::keywords::mutex_type<bs2::dummy_mutex>>::type ue_cb;

} // namespace event
} // namespace llmec

#endif /* CALLBACKS_H_ */
