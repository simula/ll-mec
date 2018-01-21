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
