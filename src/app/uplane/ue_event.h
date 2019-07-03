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
  \file ue_manager.h
  \brief managing the users and bearers, and their associations to different slices 
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#ifndef __UE_EVENT_H__
#define __UE_EVENT_H__



namespace llmec {
namespace app {
namespace uplane {

//SubscriptionType in Sec 6.3.10 Type: SubscriptionLinkList ETSI MEC 012
typedef enum {
  UE_EVENT_CELL_CHANGE          = 0,
  UE_EVENT_RAB_ESTABLISHMENT    = 1,
  UE_EVENT_RAB_MODIFICATION     = 2,
  UE_EVENT_RAB_RELEASE          = 3,
  UE_EVENT_MEAS_REPORT_UE       = 4,
  UE_EVENT_MEAS_TIMING_ADVANCE  = 5,
  UE_EVENT_CA_RECONF            = 6,
  UE_EVENT_S1_BEARER            = 7,
} ueEventType;



} // namespace uplane
} // namespace app
} // namespace llmec
#endif
