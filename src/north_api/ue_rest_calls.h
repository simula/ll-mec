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

#ifndef __UE_REST_CALLS_H__
#define __UE_REST_CALLS_H__

#include <pistache/http.h>

#include "rest_calls.h"
#include "ue_manager.h"

namespace llmec {
namespace north_api {

class Ue_rest_calls : public Rest_calls {
  public:
    Ue_rest_calls() { }
    void register_calls(Pistache::Rest::Router& router);
    void add_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_ue_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void redirect_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void delete_redirect_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void delete_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void delete_ue_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    //void obtain_stats(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
//  private:
//    std::shared_ptr<llmec::app::uplane::Ue_manager> ue_manager;
};

} // namespace north_api
} // namespace llmec


#endif

