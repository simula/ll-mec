#include <pistache/http.h>
#include "ue_rest_calls.h"
#include "json.h"
#include <iostream>
#include <string>

using json = nlohmann::json;

namespace llmec {
namespace north_api {

  void Ue_rest_calls::register_calls(Pistache::Rest::Router& router) {
    Pistache::Rest::Routes::Post(router, "/ue", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::add_ue, this));
    Pistache::Rest::Routes::Get(router, "/ue/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_ue, this));
    Pistache::Rest::Routes::Get(router, "/ue/all", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_ue_all, this));
    Pistache::Rest::Routes::Post(router, "/ue/redirect", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::redirect_ue, this));
    // TODO Move flush_flow to another rest call
    Pistache::Rest::Routes::Post(router, "/flow/flush", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::flush_flow, this));
  }

  void Ue_rest_calls::add_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string resp;
    json ue_identities_json = json::parse(request.body());

    if ( (!ue_identities_json["s1_ul_teid"].empty() && ue_identities_json["s1_ul_teid"].is_string())
        && (!ue_identities_json["s1_dl_teid"].empty() && ue_identities_json["s1_dl_teid"].is_string())
        && (!ue_identities_json["ue_ip"].empty() && ue_identities_json["ue_ip"].is_string())
        && (!ue_identities_json["enb_ip"].empty() && ue_identities_json["enb_ip"].is_string())
        ) {
      std::cout<<ue_identities_json["s1_ul_teid"].dump()<<std::endl;
      std::cout<<ue_identities_json["s1_dl_teid"].dump()<<std::endl;
      uint64_t s1_ul_teid = std::stoul(ue_identities_json["s1_ul_teid"].dump(), nullptr, 16);
      uint64_t s1_dl_teid = std::stoul(ue_identities_json["s1_dl_teid"].dump(), nullptr, 16);
      std::string ue_ip = ue_identities_json["ue_ip"];
      std::string enb_ip = ue_identities_json["enb_ip"];
      std::cout<<s1_ul_teid<<" "<<s1_dl_teid<<" "<<ue_ip<<" "<<enb_ip<<std::endl;
      this->ue_manager->add_ue(s1_ul_teid, s1_dl_teid, ue_ip, enb_ip);
      std::string resp = "OK";
      response.send(Pistache::Http::Code::Ok, resp);
      }
    else {
      resp = "Format error.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
    }
  }
  void Ue_rest_calls::redirect_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string resp;
    json payload = json::parse(request.body());
    if ( (!payload["s1_ul_teid"].empty() && payload["s1_ul_teid"].is_string())
        && (!payload["s1_dl_teid"].empty() && payload["s1_dl_teid"].is_string())
        && (!payload["ue_ip"].empty() && payload["ue_ip"].is_string())
        && (!payload["enb_ip"].empty() && payload["enb_ip"].is_string())
        && (!payload["from"].empty() && payload["from"].is_string())
        && (!payload["to"].empty() && payload["to"].is_string())
        ) {
      uint64_t s1_ul_teid = std::stoul(payload["s1_ul_teid"].dump(), nullptr, 16);
      uint64_t s1_dl_teid = std::stoul(payload["s1_dl_teid"].dump(), nullptr, 16);
      std::string ue_ip = payload["ue_ip"];
      std::string enb_ip = payload["enb_ip"];
      std::string from = payload["from"];
      std::string to = payload["to"];
      this->ue_manager->redirect_ue(s1_ul_teid, s1_dl_teid, ue_ip, enb_ip, from, to);
      std::string resp = "OK";
      response.send(Pistache::Http::Code::Ok, resp);
    }
    else {
      resp = "Format error.";
      response.send(Pistache::Http::Code::Bad_Request, resp);
    }
  }
  void Ue_rest_calls::get_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string resp = "Not implemented yet";
    response.send(Pistache::Http::Code::Ok, resp);
  }
  void Ue_rest_calls::get_ue_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string resp = "Not implemented yet";
    response.send(Pistache::Http::Code::Ok, resp);
  }
  // TODO Move this to another rest call
  void Ue_rest_calls::flush_flow(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    this->ue_manager->flush_flow(1);
    //this->ue_manager->flush_flow(0);
    std::string resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
  }

}
}
