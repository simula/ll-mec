#include <pistache/http.h>
#include "ue_rest_calls.h"

namespace llmec {
namespace north_api {

  void Ue_rest_calls::register_calls(Pistache::Rest::Router& router) {
    Pistache::Rest::Routes::Post(router, "/ue", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::add_ue, this));
    Pistache::Rest::Routes::Get(router, "/ue/:id", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_ue, this));
    Pistache::Rest::Routes::Get(router, "/ue/all", Pistache::Rest::Routes::bind(&llmec::north_api::Ue_rest_calls::get_ue_all, this));
  }

  void Ue_rest_calls::add_ue(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string ue_identities_json = request.body();

    std::string resp = "OK";
    response.send(Pistache::Http::Code::Ok, resp);
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
