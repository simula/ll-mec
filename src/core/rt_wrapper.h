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
  \file rt_wrapper.h
  \brief a wrapper around Linux OS scheduler syscall 
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
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
