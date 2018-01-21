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

#include <pistache/http.h>
#include "stats_rest_calls.h"
#include <fluid/of13/openflow-13.h>
#include <string>
#include "stats_rest_calls.h"
#include "json.h"

using json = nlohmann::json;

namespace llmec {
namespace north_api {

  void Stats_rest_calls::register_calls(Pistache::Rest::Router& router) {
    Pistache::Rest::Routes::Get(router, "/stats/flows", Pistache::Rest::Routes::bind(&llmec::north_api::Stats_rest_calls::get_flow_stats, this));
    /**
     * @api {get} /stats/flows Get all the traffic flow statistic.
     * @apiName GetFlows
     * @apiGroup Stats
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/stats/flows
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *      {"byte_count":0,"direction":"uplink","duration_sec":2098,"in_port":2,"packet_count":0,"priority":1,"table_id":0},
     *      {"byte_count":0,"direction":"downlink","duration_sec":2098,"in_port":1,"packet_count":0,"priority":1,"table_id":0}
     *     ]
     */
  }

  void Stats_rest_calls::get_flow_stats(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::shared_ptr<std::vector<fluid_msg::of13::FlowStats>> flow_stats = this->stats_manager->get_flow_stats();
    json output = json::array();
    if (flow_stats != NULL) {
      for (auto item : *flow_stats) {
        json flow;
        flow["table_id"] = item.table_id();
        flow["duration_sec"] = item.duration_sec();
        flow["priority"] = item.priority();
        flow["packet_count"] = item.packet_count();
        flow["byte_count"] = item.byte_count();
        if (item.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_TUNNEL_ID) != NULL) {
          flow["direction"] = "uplink";
          /* fluid_msg::of13::TUNNELId* tunnel_id = (fluid_msg::of13::TUNNELId*)item.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_TUNNEL_ID); */
        }
        else {
          flow["direction"] = "downlink";
        }

        if (item.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_IN_PORT) != NULL) {
          fluid_msg::of13::InPort* in_port = (fluid_msg::of13::InPort*)item.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_IN_PORT);
          flow["in_port"] = static_cast<int>(in_port->value());
        }
        else {
          flow["in_port"] = 1;
        }
        output.push_back(flow);
      }
    }
    std::string resp = output.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

}
}
