/*
 * Copyright 2016-2018 FlexRAN Authors, Eurecom and The University of Edinburgh
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * For more information about Mosaic5G:  contact@mosaic-5g.io
 */

/*! \file    task_manager.h
 *  \brief   handles the tasks within the controller
 *  \authors Xenofon Foukas
 *  \company Eurecom
 *  \email   x.foukas@sms.ed.ac.uk
 */

#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include "task.h"
#include "rib_updater.h"
#include "rt_wrapper.h"
#include "subscription.h"

#include <linux/types.h>
#include <sys/timerfd.h>

namespace llmec {
  namespace core {
    namespace rt {
      class Task_manager : public Task {
      public:
        Task_manager(llmec::mp1::rib::rib_updater& r_updater, llmec::event::subscription& ev);
        void manage_tasks();
      private:
        void wait_for_cycle();
        void run();
        llmec::mp1::rib::rib_updater& r_updater_;
        llmec::event::subscription& event_sub_;
        int sfd;
      };
    }
  }
}

#endif
