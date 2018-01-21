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
