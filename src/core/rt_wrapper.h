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
#ifndef __RT_WRAPPER_H__
#define __RT_WRAPPER_H__

#include <unistd.h> 
#include <linux/types.h>
#include <sys/syscall.h>

namespace llmec {
  namespace core {
    namespace rt {

#define gettid() syscall(__NR_gettid)

#define SCHED_DEADLINE  6
#define DEFAULT_PERIOD_NS 200000

      /* XXX use the proper syscall numbers */
#ifdef __x86_64__
#define __NR_sched_setattr   314
#define __NR_sched_getattr   315
#endif

#ifdef __i386__
#define __NR_sched_setattr   351
#define __NR_sched_getattr   352
#endif

      struct sched_attr {
        __u32 size;

        __u32 sched_policy;
        __u64 sched_flags;

        /* SCHED_NORMAL, SCHED_BATCH */
        __s32 sched_nice;

        /* SCHED_FIFO, SCHED_RR */
        __u32 sched_priority;

        /* SCHED_DEADLINE (nsec) */
        __u64 sched_runtime;
        __u64 sched_deadline;
        __u64 sched_period;
      };

      int sched_setattr(pid_t pid, const struct sched_attr *attr, unsigned int flags);

      int sched_getattr(pid_t pid,struct sched_attr *attr,unsigned int size, unsigned int flags);
    }
  }
}

#endif
