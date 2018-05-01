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
  \file app.h
  \brief apply the scheduling recepit to the LL-MEC stask
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#ifndef __APP_H__
#define __APP_H__
#include "controller_event.h"
#include "of_interface.h"
#include "task.h"
#include <iostream>

namespace llmec {
namespace app {

class App : public llmec::core::rt::Task {
  public:
    App(llmec::core::eps::OFInterface &of_interface):llmec::core::rt::Task(llmec::core::rt::Policy::DEADLINE), of_interface(of_interface) {
    }
    virtual void event_callback(llmec::core::eps::ControllerEvent* ev)=0;
    void run() {
      if (apply_scheduling_policy() < 0) {
        std::cout << "sched_setattr failed" << std::endl;
      }
      start();
    }
    virtual void start() =0;
  protected:
    llmec::core::eps::OFInterface &of_interface;
};

} // namespace app
} // namespace llmec
#endif
