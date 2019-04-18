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

#include "DefaultApiImpl.h"

namespace org {
namespace openapitools {
namespace server {
namespace api {

using namespace org::openapitools::server::model;

DefaultApiImpl::DefaultApiImpl(std::shared_ptr<Pistache::Rest::Router> rtr)
    : DefaultApi(rtr)
    { }

void DefaultApiImpl::bw_allocations_allocation_id_delete(const std::string &allocationId, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void DefaultApiImpl::bw_allocations_allocation_id_get(const std::string &allocationId, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void DefaultApiImpl::bw_allocations_allocation_id_patch(const std::string &allocationId, const BwInfoDeltas &bwInfoDeltas, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void DefaultApiImpl::bw_allocations_allocation_id_put(const std::string &allocationId, const BwInfo &bwInfo, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void DefaultApiImpl::bw_allocations_get(const Pistache::Optional<std::string> &appInsId, const Pistache::Optional<std::vector<std::string>> &applicationName, const Pistache::Optional<std::vector<std::string>> &sessionId, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}
void DefaultApiImpl::bw_allocations_post(const BwInfo &bwInfo, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}

}
}
}
}

