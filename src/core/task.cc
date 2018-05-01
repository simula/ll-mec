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
  \file task.h
  \brief task class definition
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#include "task.h"
#include <iostream>

int llmec::core::rt::Task::apply_scheduling_policy() {
  return sched_setattr(0, &sched_attr_, 0);
}

void llmec::core::rt::Task::set_scheduling_policy(Policy pol) {
  __u32 sched_policy;

  if(pol == Policy::RR) {
    sched_policy = SCHED_RR;
    sched_attr_.sched_priority = sched_get_priority_max(SCHED_RR);
  } else if (pol == Policy::FIFO) {
    sched_policy = SCHED_FIFO;
    sched_attr_.sched_priority = sched_get_priority_max(SCHED_FIFO);
  } else {
    sched_policy = SCHED_DEADLINE;
    sched_attr_.sched_priority = 0;
  }

  sched_attr_.size = sizeof(sched_attr_);
  sched_attr_.sched_flags = 0;
  sched_attr_.sched_nice = 0;

  sched_attr_.sched_policy = sched_policy;
  sched_attr_.sched_runtime  = (0.1  *  100) * 10000;
  sched_attr_.sched_deadline = DEFAULT_PERIOD_NS-30000;
  sched_attr_.sched_period   = DEFAULT_PERIOD_NS;
}
