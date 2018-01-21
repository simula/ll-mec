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
