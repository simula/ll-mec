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
    json output;
    // TODO could be handled better
    if (flow_stats != NULL) {
      for (auto item : *flow_stats) {
        /*json11::Json::object test = json11::Json::object {
          {"table_id", (int)item.table_id()},
          {"duration_sec", (double)item.duration_sec()},
          {"priority", (int)item.priority()},
          {"packet_count",(double)item.packet_count()},
          {"byte_count",(double)item.byte_count()},
        };*/
        output["table_id"] = item.table_id();
        output["duration_sec"] = item.duration_sec();
        output["priority"] = item.priority();
        output["packet_count"] = item.packet_count();
        output["byte_count"] = item.byte_count();
        if (item.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_TUNNEL_ID) != NULL) {
          output["direction"] = "uplink";
          //test.insert(std::pair<std::string, json11::Json>("direction", "uplink"));
          //std::cout<<((fluid_msg::of13::TUNNELId*)item.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_TUNNEL_ID) )->value()<<std::endl;
          fluid_msg::of13::TUNNELId* tunnel_id = (fluid_msg::of13::TUNNELId*)item.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_TUNNEL_ID);
          //std::cout<<tunnel_id->value()<<std::endl;
          //test.insert( std::pair<std::string, json11::Json>("s1_ul_tunnel_id", std::to_string(tunnel_id->value())));
        }
        else {
          output["direction"] = "downlink";
        }
        if (item.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_IN_PORT) != NULL) {
          //std::cout<<((fluid_msg::of13::InPort*)item.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_IN_PORT) )->value()<<std::endl;
          fluid_msg::of13::InPort* in_port = (fluid_msg::of13::InPort*)item.get_oxm_field(fluid_msg::of13::OFPXMT_OFB_IN_PORT);
          output["in_port"] = static_cast<int>(in_port->value());
          //test.insert( std::pair<std::string, json11::Json>("in_port", (int)(in_port->value())));
        }
        else {
          output["in_port"] = 1;
          //test.insert( std::pair<std::string, json11::Json>("in_port", 1));
        }
      }
    }
//    std::cout<<flow_stats->size()<<std::endl;
    std::string resp = output.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

}
}
