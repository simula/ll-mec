#ifndef __STATS_REST_CALLS_H__
#define __STATS_REST_CALLS_H__

#include <pistache/http.h>

#include "rest_calls.h"
#include "stats_manager.h"

namespace llmec {
namespace north_api {

class Stats_rest_calls : public Rest_calls {
  public:
    Stats_rest_calls(std::shared_ptr<llmec::app::stats::Stats_manager> stats_manager) : stats_manager(stats_manager) { }
    void register_calls(Pistache::Rest::Router& router);
    void get_switches_stats(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    //void obtain_stats(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
  private:
    std::shared_ptr<llmec::app::stats::Stats_manager> stats_manager;
};

} // namespace north_api
} // namespace llmec


#endif

