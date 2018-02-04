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

//#include <fluid/of13/openflow-13.h>
#include <string>

#include "stats_rest_calls.h"
#include "context_manager.h"
#include "ue_manager.h"
#include "utility.h"
#include "json.h"
#include "spdlog.h"

using json = nlohmann::json;

namespace llmec {
namespace north_api {

  void Stats_rest_calls::register_calls(Pistache::Rest::Router& router) {
    Pistache::Rest::Routes::Get(router, "/stats", Pistache::Rest::Routes::bind(&llmec::north_api::Stats_rest_calls::get_flow_stats, this));
    /**
     * @api {get} /stats Get all the traffic flow statistic.
     * @apiName GetFlows
     * @apiGroup Stats
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/stats
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *       {
     *         "ul":{
     *                "byte_count":0,
     *                "duration_sec":7,
     *                "packet_count":0,
     *                "priority":1,
     *                "table_id":0
     *              },
     *         "dl":{
     *                "byte_count":0,
     *                "duration_sec":7,
     *                "packet_count":0,
     *                "priority":1,
     *                "table_id":0
     *              },
     *         "enb_ip":"192.168.0.1",
     *         "eps_bearer_id":2,
     *         "id":2,
     *         "imsi":"208950000000001",
     *         "s1_dl_teid":51,
     *         "s1_ul_teid":5,
     *         "slice_id":1,
     *         "ue_ip":"172.16.0.5"
     *       },
     *       {
     *         "ul":{
     *                "byte_count":0,
     *                "duration_sec":12,
     *                "packet_count":0,
     *                "priority":1,
     *                "table_id":0
     *              },
     *         "dl":{
     *                "byte_count":0,
     *                "duration_sec":12,
     *                "packet_count":0,
     *                "priority":1,
     *                "table_id":0
     *              },
     *         "enb_ip":"192.168.0.11",
     *         "eps_bearer_id":3,
     *         "id":1,
     *         "imsi":"208950000000004",
     *         "s1_dl_teid":3,
     *         "s1_ul_teid":6,
     *         "slice_id":0,
     *         "ue_ip":"172.16.0.2"
     *       }
     *     ]
     */
    Pistache::Rest::Routes::Get(router, "/stats/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Stats_rest_calls::get_flow_stats_by_id, this));
    /**
     * @api {get} /stats/:id Get the traffic flow statistic by ID. [Default]
     * @apiName GetFlowsByID
     * @apiGroup Stats
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/stats/2
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *       {
     *         "ul":{
     *                "byte_count":0,
     *                "duration_sec":7,
     *                "packet_count":0,
     *                "priority":1,
     *                "table_id":0
     *              },
     *         "dl":{
     *                "byte_count":0,
     *                "duration_sec":7,
     *                "packet_count":0,
     *                "priority":1,
     *                "table_id":0
     *              },
     *         "enb_ip":"192.168.0.1",
     *         "eps_bearer_id":2,
     *         "id":2,
     *         "imsi":"208950000000001",
     *         "s1_dl_teid":51,
     *         "s1_ul_teid":5,
     *         "slice_id":1,
     *         "ue_ip":"172.16.0.5"
     *       }
     *     ]
     */
    Pistache::Rest::Routes::Get(router, "/stats/id/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Stats_rest_calls::get_flow_stats_by_id, this));
    /**
     * @api {get} /stats/id/:id Get the traffic flow statistic by ID. [Default]
     * @apiName GetFlowsByID
     * @apiGroup Stats
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/stats/id/2
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *       {
     *         "ul":{
     *                "byte_count":0,
     *                "duration_sec":7,
     *                "packet_count":0,
     *                "priority":1,
     *                "table_id":0
     *              },
     *         "dl":{
     *                "byte_count":0,
     *                "duration_sec":7,
     *                "packet_count":0,
     *                "priority":1,
     *                "table_id":0
     *              },
     *         "enb_ip":"192.168.0.1",
     *         "eps_bearer_id":2,
     *         "id":2,
     *         "imsi":"208950000000001",
     *         "s1_dl_teid":51,
     *         "s1_ul_teid":5,
     *         "slice_id":1,
     *         "ue_ip":"172.16.0.5"
     *       }
     *     ]
     */
    Pistache::Rest::Routes::Get(router, "/stats/imsi_bearer/:imsi_bearer", Pistache::Rest::Routes::bind(&llmec::north_api::Stats_rest_calls::get_flow_stats_by_imsi_epsbearerid, this));
    /**
     * @api {get} /stats/imsi_bearer/:imsi_bearer Get the traffic flow statistic by IMSI and EPS bearer ID. [Default]
     * @apiName GetFlowsByIMSIandBearerID
     * @apiGroup Stats
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/stats/imsi_bearer/208950000000001,2
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *       {
     *         "ul":{
     *                "byte_count":0,
     *                "duration_sec":7,
     *                "packet_count":0,
     *                "priority":1,
     *                "table_id":0
     *              },
     *         "dl":{
     *                "byte_count":0,
     *                "duration_sec":7,
     *                "packet_count":0,
     *                "priority":1,
     *                "table_id":0
     *              },
     *         "enb_ip":"192.168.0.1",
     *         "eps_bearer_id":2,
     *         "id":2,
     *         "imsi":"208950000000001",
     *         "s1_dl_teid":51,
     *         "s1_ul_teid":5,
     *         "slice_id":1,
     *         "ue_ip":"172.16.0.5"
     *       }
     *     ]
     */
  }

  void Stats_rest_calls::get_flow_stats(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    json output = json::array();
    for (auto id: ue_manager->get_bearer_id_list()) {
      json flow_stats = this->stats_manager->get_flow_stats(id);
      json bearer_stats = ue_manager->get_bearer(id);
      for (json::iterator it = bearer_stats.begin(); it != bearer_stats.end(); ++it) {
          flow_stats[it.key()] = it.value();
      }
      output.push_back(flow_stats);
    }
    std::string resp = output.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

  void Stats_rest_calls::get_flow_stats_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    std::string resp;
    auto id = request.param(":id").as<int>();
    json output = json::array();
    json flow_stats = this->stats_manager->get_flow_stats(id);
    json bearer_stats = ue_manager->get_bearer(id);
    for (json::iterator it = bearer_stats.begin(); it != bearer_stats.end(); ++it) {
      flow_stats[it.key()] = it.value();
    }
    output.push_back(flow_stats);
    resp = output.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

  void Stats_rest_calls::get_flow_stats_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    std::string resp;
    auto imsi_bearer = request.param(":imsi_bearer").as<std::string>();
    std::string imsi, bearer;
    std::vector<std::string> splited;
    llmec::util::Utility::split_string(imsi_bearer, splited, ",");
    if (splited.size() != 2) {
      resp = "Format error.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    /* simple guess to provide flexibility. Reject afterwards if no id is found */
    if (splited[0].length() == 14 || splited[0].length() == 15)
      imsi = splited[0], bearer = splited[1];
    else
      imsi = splited[1], bearer = splited[0];

    spdlog::get("ll-mec")->debug("Imsi:{} bearer id:{}", imsi, bearer);
    uint64_t id;
    uint64_t bearer_id = std::stoul(bearer, nullptr, 10);
    spdlog::get("ll-mec")->debug("Get flow stats by imsi:{} and bearer id:{}", imsi, bearer_id);
    if ((id = ue_manager->get_id(imsi, bearer_id)) == 0) {
      resp = "Imsi or bearer_id invalid.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    json output = json::array();
    json flow_stats = this->stats_manager->get_flow_stats(id);
    json bearer_stats = ue_manager->get_bearer(id);
    for (json::iterator it = bearer_stats.begin(); it != bearer_stats.end(); ++it) {
      flow_stats[it.key()] = it.value();
    }
    output.push_back(flow_stats);
    resp = output.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

}
}
