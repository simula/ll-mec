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
  void Ue_rest_calls::get_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string resp = "Not implemented yet";
    response.send(Pistache::Http::Code::Ok, resp);
  }
  void Ue_rest_calls::get_ue_all(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string resp = "Not implemented yet";
    response.send(Pistache::Http::Code::Ok, resp);
  }

}
}
