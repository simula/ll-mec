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
    void get_flow_stats(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_flow_stats_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_flow_stats_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
  private:
    std::shared_ptr<llmec::app::stats::Stats_manager> stats_manager;
};

} // namespace north_api
} // namespace llmec


#endif

