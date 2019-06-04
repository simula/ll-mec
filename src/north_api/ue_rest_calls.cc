/*
 * Copyright 2016-2018 Eurecom and Mosaic5G Platforms Authors
 * Licensed to the Mosaic5G under one or more contributor license
 * agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership.
 * The Mosaic5G licenses this file to You under the
 * Apache License, Version 2.0  (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the Mosaic5G:
 *  	contact@mosaic5g.io
 */
/*!
  \file ue_rest_calls.cc
  \brief public UE rest calls
  \author Anta Huang and N. Nikaein
  \company Eurecom
  \email: anta.huang@gmail.com, navid.nikaein@eurecom.fr
*/

#include <pistache/http.h>
#include <pistache/mime.h>
#include <iostream>
#include <string>
#include "ue_rest_calls.h"
#include "context_manager.h"
#include "json.h"
#include "spdlog.h"
#include "utility.h"

using json = nlohmann::json;

namespace llmec {
namespace north_api {

  void Ue_rest_calls::register_calls(Pistache::Rest::Router& router) {
    /* Be careful that the registered order matters */
    Pistache::Rest::Routes::Post(router, "/bearer", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::add_bearer, this));
    /**
     * @api {post} /bearer Add default/dedicated bearer context.
     * @apiName AddBearer
     * @apiGroup User
     *
     * @apiParam {Number} eps_bearer_id EPS bearer ID
     * @apiParam {Number} slice_id (optional) Slice ID. default = 0
     * @apiParam {Number} tos (optional) Type of service includeing DSCP and ECN. default = 0
     * if is choosen a different value for the meter_rate and burst_size the new MeterTable will use particular values
     * @apiParam {Number} meter_rate (optional) The rate of the drop meter rate. default = 1000000
     * @apiParam {Number} burst_size (optional) The burst size of the drop meter rate. default = 50000
     * @apiParam {String} imsi IMSI
     * @apiParam {String} s1_ul_teid S1 downlink tunnel ID
     * @apiParam {String} s1_dl_teid S1 uplink tunnel ID
     * @apiParam {String} ue_ip IP address of UE
     * @apiParam {String} enb_ip IP address of eNodeB
     * @apiExample Example usage:
     *     curl -X POST http://127.0.0.1:9999/bearer -d '{"eps_bearer_id":1, "imsi":"208950000000009", "s1_ul_teid":"0x3", "s1_dl_teid":"0x4", "ue_ip":"172.16.0.2", "enb_ip":"192.168.0.3"}'
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError BadRequest Payload format error or empty.
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Get(router, "/bearer", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_bearer_all, this));
    /**
     * @api {get} /bearer Get all bearer context.
     * @apiName GetBearers
     * @apiGroup User
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/bearer
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *      {"enb_ip":"192.168.0.3","imsi":"208950000000009","eps_bearer_id":5, "s1_dl_teid":4,"s1_ul_teid":3, "tos":0, "slice_id":0,"id":1,"ue_ip":"172.16.0.1"},
     *      {"enb_ip":"192.168.0.3","imsi":"208950000000001","eps_bearer_id":5, "s1_dl_teid":2,"s1_ul_teid":1, "tos":0, "slice_id":0,"id":2,"ue_ip":"172.16.0.2"}
     *     ]
     */
    Pistache::Rest::Routes::Get(router, "/bearer/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_bearer_by_id, this));
    /**
     * @api {get} /bearer/:id Get one specific bearer context [Default].
     * @apiName GetBearerByID
     * @apiGroup User
     * @apiParam {Number} id ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/bearer/1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *      {"id":1,"enb_ip":"192.168.0.3","imsi":"208950000000009","eps_bearer_id":5,"s1_dl_teid":4,"s1_ul_teid":3, "tos":0, "slice_id":0,"eps_bearer_id":1,"ue_ip":"172.16.0.1"}
     *     ]
     */
    Pistache::Rest::Routes::Get(router, "/bearer/id/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_bearer_by_id, this));
    /**
     * @api {get} /bearer/id/:id Get one specific bearer context By LLMEC-internally used bearer ID.
     * @apiName GetBearerByID
     * @apiGroup User
     * @apiParam {Number} id ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/bearer/id/1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *      {"id":1,"enb_ip":"192.168.0.3","imsi":"208950000000009","eps_bearer_id":5,"s1_dl_teid":4,"s1_ul_teid":3, "tos":0, "slice_id":0,"eps_bearer_id":1,"ue_ip":"172.16.0.1"}
     *     ]
     */
    Pistache::Rest::Routes::Get(router, "/bearer/imsi_bearer/:imsi_bearer", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_bearer_by_imsi_epsbearerid, this));
    /**
     * @api {get} /bearer/imsi_bearer/:imsi_bearer Get one specific bearer context by IMSI and EPS Bearer ID.
     * @apiName GetBearerByIMSIandBearerID
     * @apiGroup User
     * @apiParam {String} imsi_bearer IMSI and EPS bearer ID are concatenated by comma to from an indentity of bearer, e.g. 208950000000009,1
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/bearer/imsi_bearer/208950000000009,1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     [
     *      {"id":1,"enb_ip":"192.168.0.3","imsi":"208950000000009","eps_bearer_id":5,"s1_dl_teid":4,"s1_ul_teid":3, "tos":0, "slice_id":0, "eps_bearer_id":1,"ue_ip":"172.16.0.1"}
     *     ]
     */
    Pistache::Rest::Routes::Delete(router, "/bearer", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::delete_bearer_all, this));
    /**
     * @api {delete} /bearer Remove all bearers context.
     * @apiName DeleteBearers
     * @apiGroup User
     * @apiExample Example usage:
     *     curl -X DELETE http://127.0.0.1:9999/bearer
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Delete(router, "/bearer/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::delete_bearer_by_id, this));
    /**
     * @api {delete} /bearer/:id Remove one specific bearer context [Default].
     * @apiName DeleteBearer
     * @apiGroup User
     * @apiParam {Number} id ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)
     * @apiExample Example usage:
     *     curl -X DELETE http://127.0.0.1:9999/bearer/1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Delete(router, "/bearer/imsi_bearer/:imsi_bearer", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::delete_bearer_by_imsi_epsbearerid, this));
    /**
     * @api {delete} /bearer/imsi_bearer/:imsi_bearer Remove one specific bearer context by its IMSI and EPS bearer ID.
     * @apiName DeleteBearerByIMSIandBearerID
     * @apiGroup User
     * @apiParam {String} imsi_bearer IMSI and EPS bearer ID are concatenated by comma to from an indentity of bearer, e.g. 208950000000009,1
     * @apiExample Example usage:
     *     curl -X DELETE http://127.0.0.1:9999/bearer/imsi_bearer/208950000000009,1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Delete(router, "/bearer/id/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::delete_bearer_by_id, this));
    /**
     * @api {delete} /bearer/id/:id Remove one specific bearer context by LLMEC internally-used bearer ID.
     * @apiName DeleteBearerByID
     * @apiGroup User
     * @apiParam {Number} id ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)
     * @apiExample Example usage:
     *     curl -X DELETE http://127.0.0.1:9999/bearer/id/1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Post(router, "/bearer/redirect/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::add_redirect_bearer_by_id, this));
    /**
     * @api {post} /bearer/redirect/:id Redirect specific traffic flow for one bearer. [Default]
     * @apiName RedirectBearer
     * @apiGroup User
     *
     * @apiParam {Number} tos (optional) Type of service includeing DSCP and ECN. default = 0
     * @apiParam {String} from where the to-be-redirected traffic is coming from
     * @apiParam {String} to where the to-be-redirected traffic is going to
     *
     * @apiExample Example usage:
     *     curl -X POST http://127.0.0.1:9999/bearer/redirect/1 -d '{"from":"192.168.12.3", "to":"192.168.12.1"}'
     * @apiParam {Number} id ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)
     *
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError BadRequest Payload format error or empty.
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Post(router, "/bearer/redirect/id/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::add_redirect_bearer_by_id, this));
    /**
     * @api {post} /bearer/redirect/id/:id Redirect specific traffic flow for one bearer.
     * @apiName RedirectBearerByID
     * @apiGroup User
     *
     * @apiParam {Number} tos (optional) Type of service includeing DSCP and ECN. default = 0
     * @apiParam {String} from where the to-be-redirected traffic is coming from
     * @apiParam {String} to where the to-be-redirected traffic is going to
     *
     * @apiExample Example usage:
     *     curl -X POST http://127.0.0.1:9999/bearer/redirect/id/1 -d '{"from":"192.168.12.3", "to":"192.168.12.1"}'
     * @apiParam {Number} id ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)
     *
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError BadRequest Payload format error or empty.
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Post(router, "/bearer/redirect/imsi_bearer/:imsi_bearer", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::add_redirect_bearer_by_imsi_epsbearerid, this));
    /**
     * @api {post} /bearer/redirect/imsi_bearer/:imsi_bearer Redirect specific traffic flow for one bearer by IMSI and EPS bearer ID.
     * @apiName RedirectBearerByIMSIandBearerID
     * @apiGroup User
     *
     * @apiParam {Number} tos (optional) Type of service includeing DSCP and ECN. default = 0
     * @apiParam {String} from where the to-be-redirected traffic is coming from
     * @apiParam {String} to where the to-be-redirected traffic is going to
     *
     * @apiExample Example usage:
     *     curl -X POST http://127.0.0.1:9999/bearer/redirect/imsi_bearer/208950000000009,1 -d '{"from":"192.168.12.3", "to":"192.168.12.1"}'
     * @apiParam {String} imsi_bearer ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)
     *
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError BadRequest Payload format error or empty.
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Delete(router, "/bearer/redirect/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::delete_redirect_bearer_by_id, this));
    /**
     * @api {delete} /bearer/redirect/:id Remove the redirect flow for one bearer. [Default]
     * @apiName RemoveRedirectBearer
     * @apiGroup User
     *
     * @apiParam {Number} id ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)
     * @apiExample Example usage:
     *     curl -X DELETE http://127.0.0.1:9999/bearer/redirect/1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Delete(router, "/bearer/redirect/id/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::delete_redirect_bearer_by_id, this));
    /**
     * @api {delete} /bearer/redirect/id/:id Remove the redirect flow for one bearer by ID.
     * @apiName RemoveRedirectBearerByID
     * @apiGroup User
     *
     * @apiParam {Number} id ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)
     * @apiExample Example usage:
     *     curl -X DELETE http://127.0.0.1:9999/bearer/redirect/id/1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Delete(router, "/bearer/redirect/imsi_bearer/:imsi_bearer", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::delete_redirect_bearer_by_imsi_epsbearerid, this));
    /**
     * @api {delete} /bearer/redirect/imsi_bearer/:imsi_bearer Remove the redirect flow for one bearer by IMSI and EPS bearer ID.
     * @apiName RemoveRedirectBearerByIMSIandBearerID
     * @apiGroup User
     *
     * @apiParam {String} imsi_bearer ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)
     * @apiExample Example usage:
     *     curl -X DELETE http://127.0.0.1:9999/bearer/redirect/imsi_bearer/208950000000009,1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *
     * @apiError ServiceUnavailable Switch connection lost.
     */
    Pistache::Rest::Routes::Get(router, "/slice", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_slice_all, this));
    /**
     * @api {get} /slice Get all the slices and its containing IDs (LLMEC internally-used ID)
     * @apiName GetSlices
     * @apiGroup Slice
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/slice
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     {
     *       "1":[2],
     *       "4":[1]
     *     }
     */
    Pistache::Rest::Routes::Get(router, "/slice/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_slice_by_id, this));
    /**
     * @api {get} /slice/:id Get one indicated slice and its containing IDs (LLMEC internally-used ID)
     * @apiName GetSliceByID
     * @apiGroup Slice
     * @apiExample Example usage:
     *     curl -X GET http://127.0.0.1:9999/slice/1
     * @apiSuccessExample Success-Response:
     *     HTTP/1.1 200 OK
     *     {
     *       "1":[2]
     *     }
     */
  }

  void Ue_rest_calls::add_bearer(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    std::string resp;
    if (request.body().empty()) {
      resp = "Bearer identities required.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    json payload = json::parse(request.body());
    if ( (payload["eps_bearer_id"].empty() || !payload["eps_bearer_id"].is_number())
	      || (payload["imsi"].empty() || !payload["imsi"].is_string())
        || (payload["s1_ul_teid"].empty() || !payload["s1_ul_teid"].is_string())
        || (payload["s1_dl_teid"].empty() || !payload["s1_dl_teid"].is_string())
        || (payload["ue_ip"].empty() || !payload["ue_ip"].is_string())
        || (payload["enb_ip"].empty() || !payload["enb_ip"].is_string())
//        || (payload["meter_rate"].empty() || !payload["meter_rate"].is_number())
//        || (payload["burst_size"].empty() || !payload["burst_size"].is_number())
        ) {
      resp = "Format error.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    spdlog::get("ll-mec")->debug("string s1_ul_teid {}, s1_dl_teid {}", payload["s1_ul_teid"].get<std::string>(), payload["s1_dl_teid"].get<std::string>());
    uint64_t s1_ul_teid = std::stoul(payload["s1_ul_teid"].get<std::string>(), nullptr, 16);
    uint64_t s1_dl_teid = std::stoul(payload["s1_dl_teid"].get<std::string>(), nullptr, 16);
    spdlog::get("ll-mec")->debug("number s1_ul_teid {}, s1_dl_teid {}", s1_ul_teid, s1_dl_teid);
    std::string ue_ip = payload["ue_ip"];
    std::string enb_ip = payload["enb_ip"];
    uint64_t eps_bearer_id = payload["eps_bearer_id"].get<int>();
    std::string imsi = payload["imsi"].get<std::string>();
//    uint32_t meter_rate = payload["meter_rate"].get<int>();
//    uint32_t burst_size = payload["burst_size"].get<int>();
    uint64_t slice_id = 0;
    if (!payload["slice_id"].empty()) {
      if (!payload["slice_id"].is_number()) {
        resp = "Slice id is not a valid number.";
        response.send(Pistache::Http::Code::Bad_Request, resp);
        return;
      }
      slice_id = payload["slice_id"].get<int>();
    }
    uint8_t tos = 0;
    if (!payload["tos"].empty()) {
      if (!payload["tos"].is_number()) {
        resp = "ToS is not a valid number.";
        response.send(Pistache::Http::Code::Bad_Request, resp);
        return;
      }
      tos = payload["tos"].get<int>();
    }
    /*
     * Optional metering parameters for defining the DefaultMeterTable
     *
     */
     uint32_t meter_rate = 1000000;
     if (!payload["meter_rate"].empty()){
      if (!payload["meter_rate"].is_number()) {
        resp = "Meter Rate is not a valid number.";
        response.send(Pistache::Http::Code::Bad_Request, resp);
        return;
      }
      meter_rate = payload["meter_rate"].get<int>();
    }
    uint32_t burst_size = 50000;
    if (!payload["burst_size"].empty()){
      if (!payload["burst_size"].is_number()) {
        resp = "Meter Burst Size is not a valid number.";
        response.send(Pistache::Http::Code::Bad_Request, resp);
        return;
      }
      burst_size = payload["burst_size"].get<int>();
    }

    spdlog::get("ll-mec")->debug("eps_bearer_id {}, imsi {}, meter_rate {}, burst_size {}", eps_bearer_id, imsi, meter_rate, burst_size);

    /* Create a new json to have clean content */
    json context = {
      {"imsi", imsi},
      {"eps_bearer_id", eps_bearer_id},
      {"s1_ul_teid", s1_ul_teid},
      {"s1_dl_teid", s1_dl_teid},
      {"ue_ip", ue_ip},
      {"enb_ip", enb_ip},
      {"slice_id", slice_id},
      {"tos", tos},
      {"meter_rate", meter_rate},
      {"burst_size", burst_size}
    };
    if (ue_manager->add_bearer(context) == false) {
      resp = "Switch connection lost.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::add_redirect_bearer_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    std::string resp;
    if (request.body().empty()) {
      resp = "Payload is empty. Redirect information required.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    auto id = request.param(":id").as<int>();
    json payload = json::parse(request.body());
    if ( (payload["from"].empty() || !payload["from"].is_string())
        || (payload["to"].empty() || !payload["to"].is_string())
        ) {
      resp = "Format error.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }

    std::string from = payload["from"];
    std::string to = payload["to"];

    uint8_t tos = 0;
    if (!payload["tos"].empty()) {
      if (!payload["tos"].is_number()) {
        resp = "ToS is not a valid number.";
        response.send(Pistache::Http::Code::Bad_Request, resp);
        return;
      }
      tos = payload["tos"].get<int>();
    }
    json context = {
      {"from", from},
      {"to", to},
      {"tos", tos}
    };

    if (ue_manager->add_redirect_bearer(id, context) == false) {
      resp = "Switch connection lost or no such bearer is found.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::add_redirect_bearer_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    std::string resp;
    if (request.body().empty()) {
      resp = "Payload is empty. Redirect information required.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
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
    spdlog::get("ll-mec")->debug("Get UE by imsi:{} and bearer id:{}", imsi, bearer_id);
    if ((id = ue_manager->get_id(imsi, bearer_id)) == 0) {
      resp = "Imsi or bearer_id invalid.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    json payload = json::parse(request.body());
    if ( (payload["from"].empty() || !payload["from"].is_string())
        || (payload["to"].empty() || !payload["to"].is_string())
        ) {
      resp = "Format error.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }

    std::string from = payload["from"];
    std::string to = payload["to"];

    uint8_t tos = 0;
    if (!payload["tos"].empty()) {
      if (!payload["tos"].is_number()) {
        resp = "ToS is not a valid number.";
        response.send(Pistache::Http::Code::Bad_Request, resp);
        return;
      }
      tos = payload["tos"].get<int>();
    }
    json context = {
      {"from", from},
      {"to", to},
      {"tos", tos}
    };

    if (ue_manager->add_redirect_bearer(id, context) == false) {
      resp = "Switch connection lost or no such bearer is found.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::delete_redirect_bearer_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    /* Take eps_bearer_id as ue_id */
    auto id = request.param(":id").as<int>();
    std::string resp;
    if (ue_manager->delete_redirect_bearer(id) == false) {
      resp = "Switch connection lost or no such bearer is found.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::delete_redirect_bearer_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    std::string resp;
    /* Take eps_bearer_id as ue_id */
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
    spdlog::get("ll-mec")->debug("Get UE by imsi:{} and bearer id:{}", imsi, bearer_id);
    if ((id = ue_manager->get_id(imsi, bearer_id)) == 0) {
      resp = "Imsi or bearer_id invalid.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    if (ue_manager->delete_redirect_bearer(id) == false) {
      resp = "Switch connection lost or no such bearer is found.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::get_bearer_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    auto id = request.param(":id").as<int>();
    json bearer = ue_manager->get_bearer(id);
    std::string resp = bearer.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

  void Ue_rest_calls::get_bearer_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
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
    spdlog::get("ll-mec")->debug("Get UE by imsi:{} and bearer id:{}", imsi, bearer_id);
    if ((id = ue_manager->get_id(imsi, bearer_id)) == 0) {
      resp = "Imsi or bearer_id invalid.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }
    spdlog::get("ll-mec")->debug("The corresponding id is {}", id);
    json payload = ue_manager->get_bearer(id);
    resp = payload.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

  void Ue_rest_calls::get_bearer_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    auto m = MIME(Application, Json);
    json bearer_all = ue_manager->get_bearer_all();
    std::string resp = bearer_all.dump();
    response.send(Pistache::Http::Code::Ok, resp, m);
  }

  void Ue_rest_calls::delete_bearer_by_imsi_epsbearerid(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    std::string resp;

    /* the expected format is "imsi,bearer_id" */
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

    uint64_t id;
    uint64_t bearer_id = std::stoul(bearer, nullptr, 10);
    if ((id = ue_manager->get_id(imsi, bearer_id)) == 0) {
      resp = "Imsi or bearer_id invalid.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }

    if (ue_manager->delete_bearer(id) == false) {
      resp = "Switch connection lost.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::delete_bearer_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    std::string resp;

    /* the expected format is "imsi,bearer_id" */
    auto id = request.param(":id").as<int>();

    /* Default flow will be labled as 0 and cannot be removed */
    if (id == 0) {
      resp = "Default flows (id = 0) cannot be deleted.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }

    /* ID not exist */
    if (ue_manager->id_exist(id) == false) {
      resp = "ID invalid.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
      return;
    }

    if (ue_manager->delete_bearer(id) == false) {
      resp = "Switch connection lost.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::delete_bearer_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    std::string resp;
    if (ue_manager->delete_bearer_all() == false) {
      resp = "Switch connection lost.";
      response.send(Pistache::Http::Code::Service_Unavailable, resp);
      return;
    }
    resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
    return;
  }

  void Ue_rest_calls::get_slice_by_id(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    auto id = request.param(":id").as<int>();
    json slice = ue_manager->get_slice(id);
    std::string resp = slice.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

  void Ue_rest_calls::get_slice_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    llmec::app::uplane::Ue_manager* ue_manager = llmec::app::uplane::Ue_manager::get_instance();
    json slices = ue_manager->get_slice_all();
    std::string resp = slices.dump();
    response.send(Pistache::Http::Code::Ok, resp);
  }

}
}
