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

/*! \file    task_manager.cc
 *  \brief   handles the tasks within the controller
 *  \authors Xenofon Foukas, Robert Schmidt
 *  \company Eurecom
 *  \email   x.foukas@sms.ed.ac.uk, robert.schmidt@eurecom.fr
 */

#include <thread>
#include <unistd.h>
#include <iostream>
#include "spdlog.h"
#include "task_manager.h"

llmec::core::rt::Task_manager::Task_manager(
    llmec::mp1::rib::rib_updater &r_updater, llmec::event::subscription &ev)
    :
    Task(llmec::core::rt::Policy::FIFO),
    r_updater_(r_updater),
    event_sub_(ev) {
  struct itimerspec its;

  sfd = timerfd_create(CLOCK_MONOTONIC, 0);

  /* Start the timer */
  its.it_value.tv_sec = 0;
  its.it_value.tv_nsec = 1000 * 1000;
  its.it_interval.tv_sec = its.it_value.tv_sec;
  its.it_interval.tv_nsec = its.it_value.tv_nsec;

  if (timerfd_settime(sfd, TFD_TIMER_ABSTIME, &its, NULL) == -1) {
    spdlog::get("ll-mec")->error("Failed to set timer for task manager");
  }
}

void llmec::core::rt::Task_manager::run() {
  manage_tasks();
}

void llmec::core::rt::Task_manager::manage_tasks() {
  uint64_t t = 0;
  std::chrono::steady_clock::time_point loop_start;
  std::chrono::duration<float, std::micro> loop_dur;

  // First run the RIB updater
  r_updater_.run();

  while (1) {
    event_sub_.task_tick(t);
    //event_sub_.last_tick = t;
    t++;
    wait_for_cycle();
  }
}

void llmec::core::rt::Task_manager::wait_for_cycle() {
  uint64_t exp;
  ssize_t res;

  if (sfd > 0) {
    res = read(sfd, &exp, sizeof(exp));
    if ((res < 0) || (res != sizeof(exp))) {
      spdlog::get("ll-mec")->error("Failed in task manager timer wait");
    }
  }
}
