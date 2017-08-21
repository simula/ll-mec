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
