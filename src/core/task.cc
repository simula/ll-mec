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
