/**
* BWM API
* The ETSI MEC ISG MEC015 Bandwidth Management API described using OpenAPI
*
* OpenAPI spec version: 1.1.1
* 
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/

#include "DefaultApi.h"
#include "Helpers.h"

namespace org {
namespace llmec {
namespace mp2 {
namespace api {

//This namespace has to remain the same. It is corelated with the Helpers.h
using namespace org::openapitools::server::helpers;
//This namespace it is corelated with DefaultApi.h
using namespace org::llmec::mp2::model;

DefaultApi::DefaultApi(std::shared_ptr<Pistache::Rest::Router> rtr) { 
    router = rtr;
};

void DefaultApi::init() {
    setupRoutes();
}

void DefaultApi::setupRoutes() {
    using namespace Pistache::Rest;

    Routes::Delete(*router, base + "/bw_allocations/:allocationId", Routes::bind(&DefaultApi::bw_allocations_allocation_id_delete_handler, this));
    Routes::Get(*router, base + "/bw_allocations/:allocationId", Routes::bind(&DefaultApi::bw_allocations_allocation_id_get_handler, this));
    Routes::Patch(*router, base + "/bw_allocations/:allocationId", Routes::bind(&DefaultApi::bw_allocations_allocation_id_patch_handler, this));
    Routes::Put(*router, base + "/bw_allocations/:allocationId", Routes::bind(&DefaultApi::bw_allocations_allocation_id_put_handler, this));
    Routes::Get(*router, base + "/bw_allocations", Routes::bind(&DefaultApi::bw_allocations_get_handler, this));
    Routes::Post(*router, base + "/bw_allocations", Routes::bind(&DefaultApi::bw_allocations_post_handler, this));

    // Default handler, called when a route is not found
    router->addCustomHandler(Routes::bind(&DefaultApi::default_api_default_handler, this));
}

void DefaultApi::bw_allocations_allocation_id_delete_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    // Getting the path params
    auto allocationId = request.param(":allocationId").as<std::string>();
    
    try {
      this->bw_allocations_allocation_id_delete(allocationId, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void DefaultApi::bw_allocations_allocation_id_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    // Getting the path params
    auto allocationId = request.param(":allocationId").as<std::string>();
    
    try {
      this->bw_allocations_allocation_id_get(allocationId, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void DefaultApi::bw_allocations_allocation_id_patch_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    // Getting the path params
    auto allocationId = request.param(":allocationId").as<std::string>();
    
    // Getting the body param
    
    BwInfoDeltas bwInfoDeltas;
    
    try {
      nlohmann::json request_body = nlohmann::json::parse(request.body());
    
      bwInfoDeltas.fromJson(request_body);
    
      this->bw_allocations_allocation_id_patch(allocationId, bwInfoDeltas, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void DefaultApi::bw_allocations_allocation_id_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    // Getting the path params
    auto allocationId = request.param(":allocationId").as<std::string>();
    
    // Getting the body param
    
    BwInfo bwInfo;
    
    try {
      nlohmann::json request_body = nlohmann::json::parse(request.body());
    
      bwInfo.fromJson(request_body);
    
      this->bw_allocations_allocation_id_put(allocationId, bwInfo, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void DefaultApi::bw_allocations_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

    // Getting the query params
    auto appInsIdQuery = request.query().get("app_ins_id");
    Pistache::Optional<std::string> appInsId;
    if(!appInsIdQuery.isEmpty()){
        std::string value;
        if(fromStringValue(appInsIdQuery.get(), value)){
            appInsId = Pistache::Some(value);
        }
    }
    auto applicationNameQuery = request.query().get("application_name");
    Pistache::Optional<std::vector<std::string>> applicationName;
    if(!applicationNameQuery.isEmpty()){
        std::vector<std::string> value;
        if(fromStringValue(applicationNameQuery.get(), value)){
            applicationName = Pistache::Some(value);
        }
    }
    auto sessionIdQuery = request.query().get("session_id");
    Pistache::Optional<std::vector<std::string>> sessionId;
    if(!sessionIdQuery.isEmpty()){
        std::vector<std::string> value;
        if(fromStringValue(sessionIdQuery.get(), value)){
            sessionId = Pistache::Some(value);
        }
    }
    
    try {
      this->bw_allocations_get(appInsId, applicationName, sessionId, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void DefaultApi::bw_allocations_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

    // Getting the body param
    
    BwInfo bwInfo;
    
    try {
      nlohmann::json request_body = nlohmann::json::parse(request.body());
    
      bwInfo.fromJson(request_body);
    
      this->bw_allocations_post(bwInfo, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}

void DefaultApi::default_api_default_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Not_Found, "The requested method does not exist");
}

}
}
}
}

