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


#include "InlineObject4.h"

namespace org {
namespace openapitools {
namespace server {
namespace model {

Inline_object_4::Inline_object_4()
{
    m_MeasTaSubscriptionIsSet = false;
    
}

Inline_object_4::~Inline_object_4()
{
}

void Inline_object_4::validate()
{
    // TODO: implement validation
}

nlohmann::json Inline_object_4::toJson() const
{
    nlohmann::json val = nlohmann::json::object();

    if(m_MeasTaSubscriptionIsSet)
    {
        val["MeasTaSubscription"] = ModelBase::toJson(m_MeasTaSubscription);
    }
    

    return val;
}

void Inline_object_4::fromJson(const nlohmann::json& val)
{
    if(val.find("MeasTaSubscription") != val.end())
    {
        if(!val["MeasTaSubscription"].is_null())
        {
            MeasTaSubscriptionPost newItem;
            newItem.fromJson(val["MeasTaSubscription"]);
            setMeasTaSubscription( newItem );
        }
        
    }
    
}


MeasTaSubscriptionPost Inline_object_4::getMeasTaSubscription() const
{
    return m_MeasTaSubscription;
}
void Inline_object_4::setMeasTaSubscription(MeasTaSubscriptionPost const& value)
{
    m_MeasTaSubscription = value;
    m_MeasTaSubscriptionIsSet = true;
}
bool Inline_object_4::measTaSubscriptionIsSet() const
{
    return m_MeasTaSubscriptionIsSet;
}
void Inline_object_4::unsetMeasTaSubscription()
{
    m_MeasTaSubscriptionIsSet = false;
}

}
}
}
}

