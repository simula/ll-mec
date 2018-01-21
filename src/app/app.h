/* The MIT License (MIT)

   Copyright (c) 2018 Anta Huang (anta.huang@eurecom.fr)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
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
