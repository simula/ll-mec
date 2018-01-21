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

#ifndef __TASK_H__
#define __TASK_H__

#include <thread>
#include "rt_wrapper.h"

namespace llmec {
  namespace core {
    namespace rt {
      enum class Policy {RR = SCHED_RR, DEADLINE = SCHED_DEADLINE, FIFO = SCHED_FIFO};
      class Task {
        public:
          Task(Policy pol) {
            set_scheduling_policy(pol);
          }
          virtual void run()=0;
          int apply_scheduling_policy();
        protected:
          struct sched_attr sched_attr_;
        private:
          void set_scheduling_policy(Policy pol);
      };
    }
  }
}
#endif
