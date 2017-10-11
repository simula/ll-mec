#ifndef __UE_REST_CALLS_H__
#define __UE_REST_CALLS_H__

#include <pistache/http.h>

#include "rest_calls.h"
#include "ue_manager.h"

namespace llmec {
namespace north_api {

class Ue_rest_calls : public Rest_calls {
  public:
    Ue_rest_calls(std::shared_ptr<llmec::app::uplane::Ue_manager> ue_manager) : ue_manager(ue_manager) { }
    void register_calls(Pistache::Rest::Router& router);
    void add_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_ue_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    //void obtain_stats(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
  private:
    std::shared_ptr<llmec::app::uplane::Ue_manager> ue_manager;
};

} // namespace north_api
} // namespace llmec


#endif

