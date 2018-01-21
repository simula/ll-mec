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
#include <iostream>
#include <string>
#include "ue_rest_calls.h"
#include "json.h"
#include "spdlog.h"

using json = nlohmann::json;

namespace llmec {
namespace north_api {

  void Ue_rest_calls::register_calls(Pistache::Rest::Router& router) {
    /* Be careful that the registered order matters */
    Pistache::Rest::Routes::Post(router, "/ue", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::add_ue, this));
    /**
     * @api {post} /ue Add UE context.
     * @apiName AddUE
     * @apiGroup User
     *
     * @apiParam {Number} eps_bearer_id EPS bearer ID
     * @apiParam {String} imsi IMSI
     * @apiParam {String} s1_ul_teid S1 downlink tunnel ID
     * @apiParam {String} s1_dl_teid S1 uplink tunnel ID
     * @apiParam {String} ue_ip IP address of UE
     * @apiParam {String} enb_ip IP address of eNodeB
     * @apiExample Example usage:
     *     curl -X POST http://127.0.0.1:9999/ue -d '{"eps_bearer_id":1, "imsi":"208950000000009", "s1_ul_teid":"0x3", "s1_dl_teid":"0x4", "ue_ip":"172.16.0.2", "enb_ip":"192.168.0.3"}'
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError BadRequest Payload format error or empty.
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Get(router, "/ue", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_ue_all, this));
    /**
     * @api {get} /ue Get all UE context.
     * @apiName GetUEs
     * @apiGroup User
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/ue
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *      {"enb_ip":"192.168.0.3","imsi":"208950000000009","s1_dl_teid":4,"s1_ul_teid":3,"ue_id":1,"ue_ip":"172.16.0.1"},
     *      {"enb_ip":"192.168.0.3","imsi":"208950000000001","s1_dl_teid":2,"s1_ul_teid":1,"ue_id":2,"ue_ip":"172.16.0.2"}
     *     ]
     */
    Pistache::Rest::Routes::Get(router, "/ue/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_ue, this));
    /**
     * @api {get} /ue/:id Get one specific UE context.
     * @apiName GetUE
     * @apiGroup User
     * @apiParam {Number} id UE id (EPS bearer id) of the user
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/ue/1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *      {"enb_ip":"192.168.0.3","imsi":"208950000000009","s1_dl_teid":4,"s1_ul_teid":3,"ue_id":1,"ue_ip":"172.16.0.1"}
     *     ]
     */
    Pistache::Rest::Routes::Delete(router, "/ue", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::delete_ue_all, this));
    /**
     * @api {delete} /ue Remove all UE context.
     * @apiName DeleteUEs
     * @apiGroup User
     * @apiExample Example usage:
     *     curl -X DELETE http://127.0.0.1:9999/ue
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Delete(router, "/ue/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::delete_ue, this));
    /**
     * @api {delete} /ue/:id Remove one specific UE context.
     * @apiName DeleteUE
     * @apiGroup User
     * @apiParam {Number} id UE id (EPS bearer id) of the user
     * @apiExample Example usage:
     *     curl -X DELETE http://127.0.0.1:9999/ue/1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Post(router, "/ue/redirect/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::redirect_ue, this));
    /**
     * @api {post} /ue/redirect/:id Redirect specific traffic flow for one UE.
     * @apiName RedirectUE
     * @apiGroup User
     *
     * @apiParam {Number} id UE id (EPS bearer ID)
     * @apiParam {String} s1_ul_teid S1 downlink tunnel ID
     * @apiParam {String} s1_dl_teid S1 uplink tunnel ID
     * @apiParam {String} ue_ip IP address of UE
     * @apiParam {String} enb_ip IP address of eNodeB
     * @apiParam {String} from where the to-be-redirected traffic is coming from
     * @apiParam {String} to where the to-be-redirected traffic is going to
     *
     * @apiExample Example usage:
     *     curl -X POST http://127.0.0.1:9999/ue/redirect/1 -d '{"s1_ul_teid":"0x3", "s1_dl_teid":"0x4", "ue_ip":"172.16.0.2", "enb_ip":"192.168.0.3", "from":"192.168.12.3", "to":"192.168.12.1"}'
     * @apiParam {Number} id UE id (EPS bearer id) of the user
     *
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError BadRequest Payload format error or empty.
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Delete(router, "/ue/redirect/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::delete_redirect_ue, this));
    /**
     * @api {delete} /ue/redirect/:id Remove the redirect flow for one UE.
     * @apiName RemoveRedirectUE
     * @apiGroup User
     *
     * @apiParam {Number} id UE id (EPS bearer id) of the user
     * @apiExample Example usage:
     *     curl -X DELETE http://127.0.0.1:9999/ue/redirect/1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError ServiceUnavailable Switch connection lost.
     */
  }

  void Ue_rest_calls::add_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string resp;
    if (request.body().empty()) {
      resp = "UE identities required.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    json ue_identities_json = json::parse(request.body());
    if ( (ue_identities_json["eps_bearer_id"].empty() || !ue_identities_json["eps_bearer_id"].is_number())
        || (ue_identities_json["imsi"].empty() || !ue_identities_json["imsi"].is_string())
        || (ue_identities_json["s1_ul_teid"].empty() || !ue_identities_json["s1_ul_teid"].is_string())
        || (ue_identities_json["s1_dl_teid"].empty() || !ue_identities_json["s1_dl_teid"].is_string())
        || (ue_identities_json["ue_ip"].empty() || !ue_identities_json["ue_ip"].is_string())
        || (ue_identities_json["enb_ip"].empty() || !ue_identities_json["enb_ip"].is_string())
        ) {
      resp = "Format error.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    spdlog::get("ll-mec")->debug("string s1_ul_teid {}, s1_dl_teid {}", ue_identities_json["s1_ul_teid"].get<std::string>(), ue_identities_json["s1_dl_teid"].get<std::string>());
    uint64_t s1_ul_teid = std::stoul(ue_identities_json["s1_ul_teid"].get<std::string>(), nullptr, 16);
    uint64_t s1_dl_teid = std::stoul(ue_identities_json["s1_dl_teid"].get<std::string>(), nullptr, 16);
    spdlog::get("ll-mec")->debug("number s1_ul_teid {}, s1_dl_teid {}", s1_ul_teid, s1_dl_teid);
    std::string ue_ip = ue_identities_json["ue_ip"];
    std::string enb_ip = ue_identities_json["enb_ip"];
    uint64_t ue_id = ue_identities_json["eps_bearer_id"].get<int>();
    std::string imsi = ue_identities_json["imsi"].get<std::string>();
    spdlog::get("ll-mec")->debug("eps_bearer_id {}, imsi {}", ue_id, imsi);
    if (this->ue_manager->add_ue(ue_id, imsi, s1_ul_teid, s1_dl_teid, ue_ip, enb_ip) == false) {
      resp = "Switch connection lost.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::redirect_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string resp;
    if (request.body().empty()) {
      resp = "Payload is empty. Redirect information required.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    auto ue_id = request.param(":id").as<int>();
    json payload = json::parse(request.body());
    if ( (payload["s1_ul_teid"].empty() || !payload["s1_ul_teid"].is_string())
        || (payload["s1_dl_teid"].empty() || !payload["s1_dl_teid"].is_string())
        || (payload["ue_ip"].empty() || !payload["ue_ip"].is_string())
        || (payload["enb_ip"].empty() || !payload["enb_ip"].is_string())
        || (payload["from"].empty() || !payload["from"].is_string())
        || (payload["to"].empty() || !payload["to"].is_string())
        ) {
      resp = "Format error.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    uint64_t s1_ul_teid = std::stoul(payload["s1_ul_teid"].get<std::string>(), nullptr, 16);
    uint64_t s1_dl_teid = std::stoul(payload["s1_dl_teid"].get<std::string>(), nullptr, 16);
    std::string ue_ip = payload["ue_ip"];

    std::string enb_ip = payload["enb_ip"];
    std::string from = payload["from"];
    std::string to = payload["to"];

    if (this->ue_manager->redirect_ue(ue_id, s1_ul_teid, s1_dl_teid, ue_ip, enb_ip, from, to) == false) {
      resp = "Switch connection lost.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::delete_redirect_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    /* Take eps_bearer_id as ue_id */
    auto ue_id = request.param(":id").as<int>();
    std::string resp;
    if (this->ue_manager->delete_redirect_ue(ue_id) == false) {
      resp = "Switch connection lost.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::get_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    auto ue_id = request.param(":id").as<int>();
    json ue = this->ue_manager->get_ue(ue_id);
    std::string resp = ue.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

  void Ue_rest_calls::get_ue_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    json ue_all = this->ue_manager->get_ue_all();
    std::string resp = ue_all.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

  void Ue_rest_calls::delete_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    /* Take eps_bearer_id as ue_id */
    auto ue_id = request.param(":id").as<int>();
    std::string resp;
    if (this->ue_manager->delete_ue(ue_id) == false) {
      resp = "Switch connection lost.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::delete_ue_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string resp;
    if (this->ue_manager->delete_ue_all() == false) {
      resp = "Switch connection lost.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }
}
}
