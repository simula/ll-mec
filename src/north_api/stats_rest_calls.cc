#include <pistache/http.h>
#include "stats_rest_calls.h"

namespace llmec {
namespace north_api {

  void Stats_rest_calls::register_calls(Pistache::Rest::Router& router) {
    Pistache::Rest::Routes::Get(router, "/switch/all", Pistache::Rest::Routes::bind(&llmec::north_api::Stats_rest_calls::get_switches_stats, this));
  }

  void Stats_rest_calls::get_switches_stats(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
  }

}
}
