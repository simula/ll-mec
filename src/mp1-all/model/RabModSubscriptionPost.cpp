/**
* RNI API
* The ETSI MEC ISG MEC012 Radio Network Information API described using OpenAPI
*
* OpenAPI spec version: 1.1.1
* 
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/


#include "RabModSubscriptionPost.h"

namespace org {
namespace openapitools {
namespace server {
namespace model {

RabModSubscriptionPost::RabModSubscriptionPost()
{
    m_CallbackReference = "";
    m_ExpiryDeadlineIsSet = false;
    
}

RabModSubscriptionPost::~RabModSubscriptionPost()
{
}

void RabModSubscriptionPost::validate()
{
    // TODO: implement validation
}

nlohmann::json RabModSubscriptionPost::toJson() const
{
    nlohmann::json val = nlohmann::json::object();

    val["callbackReference"] = ModelBase::toJson(m_CallbackReference);
    val["filterCriteria"] = ModelBase::toJson(m_FilterCriteria);
    if(m_ExpiryDeadlineIsSet)
    {
        val["expiryDeadline"] = ModelBase::toJson(m_ExpiryDeadline);
    }
    

    return val;
}

void RabModSubscriptionPost::fromJson(const nlohmann::json& val)
{
    setCallbackReference(val.at("callbackReference"));
    if(val.find("expiryDeadline") != val.end())
    {
        if(!val["expiryDeadline"].is_null())
        {
            TimeStamp newItem;
            newItem.fromJson(val["expiryDeadline"]);
            setExpiryDeadline( newItem );
        }
        
    }
    
}


std::string RabModSubscriptionPost::getCallbackReference() const
{
    return m_CallbackReference;
}
void RabModSubscriptionPost::setCallbackReference(std::string const& value)
{
    m_CallbackReference = value;
    
}
FilterCriteriaAssocQci RabModSubscriptionPost::getFilterCriteria() const
{
    return m_FilterCriteria;
}
void RabModSubscriptionPost::setFilterCriteria(FilterCriteriaAssocQci const& value)
{
    m_FilterCriteria = value;
    
}
TimeStamp RabModSubscriptionPost::getExpiryDeadline() const
{
    return m_ExpiryDeadline;
}
void RabModSubscriptionPost::setExpiryDeadline(TimeStamp const& value)
{
    m_ExpiryDeadline = value;
    m_ExpiryDeadlineIsSet = true;
}
bool RabModSubscriptionPost::expiryDeadlineIsSet() const
{
    return m_ExpiryDeadlineIsSet;
}
void RabModSubscriptionPost::unsetExpiryDeadline()
{
    m_ExpiryDeadlineIsSet = false;
}

}
}
}
}

