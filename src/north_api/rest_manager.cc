#include <iostream>

#include "rest_manager.h"

namespace llmec {
namespace north_api {

void Rest_manager::init(size_t thr) {
  auto opts = Pistache::Http::Endpoint::options().threads(thr);
  httpEndpoint->init(opts);
}

void Rest_manager::start() {
  httpEndpoint->setHandler(router_.handler());
  httpEndpoint->serve();
}

void Rest_manager::shutdown() {
  httpEndpoint->shutdown();
}

void Rest_manager::register_calls(llmec::north_api::Rest_calls& calls) {
  calls.register_calls(router_);
}

} // namespace north_api
} // namespace llmec
