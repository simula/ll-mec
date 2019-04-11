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


#include "SubscriptionLinkList.h"

namespace org {
namespace openapitools {
namespace server {
namespace model {

SubscriptionLinkList::SubscriptionLinkList()
{
    m_SubscriptionIsSet = false;
    
}

SubscriptionLinkList::~SubscriptionLinkList()
{
}

void SubscriptionLinkList::validate()
{
    // TODO: implement validation
}

nlohmann::json SubscriptionLinkList::toJson() const
{
    nlohmann::json val = nlohmann::json::object();

    val["_links"] = ModelBase::toJson(m__links);
    {
        nlohmann::json jsonArray;
        for( const auto& item : m_Subscription )
        {
            jsonArray.push_back(ModelBase::toJson(item));
        }
        
        if(jsonArray.size() > 0)
        {
            val["subscription"] = jsonArray;
        } 
    }
    

    return val;
}

void SubscriptionLinkList::fromJson(const nlohmann::json& val)
{
    {
        m_Subscription.clear();
        if(val.find("subscription") != val.end())
        {
            for( const auto& item : val["subscription"] )
            {
                
                if(item.is_null())
                {
                    m_Subscription.push_back( Subscription() );
                }
                else
                {
                    Subscription newItem;
                    newItem.fromJson(item);
                    m_Subscription.push_back( newItem );
                }
                
            }
        }
    }
    
}


Link SubscriptionLinkList::getLinks() const
{
    return m__links;
}
void SubscriptionLinkList::setLinks(Link const& value)
{
    m__links = value;
    
}
std::vector<Subscription>& SubscriptionLinkList::getSubscription()
{
    return m_Subscription;
}
bool SubscriptionLinkList::subscriptionIsSet() const
{
    return m_SubscriptionIsSet;
}
void SubscriptionLinkList::unsetSubscription()
{
    m_SubscriptionIsSet = false;
}

}
}
}
}

