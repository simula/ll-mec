#ifndef __REST_MANAGER_H_
#define __REST_MANAGER_H_

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "rest_calls.h"

namespace llmec {
namespace north_api {

class Rest_manager {
  public:
    Rest_manager(Pistache::Address address) : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(address)) { }
    void init(size_t thr = 1);
    void start();
    void shutdown();
    void register_calls(llmec::north_api::Rest_calls& calls);

  private:
    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router router_;
};

} // namespace north_api
} // namespace llmec

#endif
