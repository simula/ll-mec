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
/*
 * SubscriptionType.h
 *
 * Numeric value corresponding to specified type of subscription.
 */

#ifndef SubscriptionType_H_
#define SubscriptionType_H_


#include "ModelBase.h"


namespace org {
namespace openapitools {
namespace server {
namespace model {

/// <summary>
/// Numeric value corresponding to specified type of subscription.
/// </summary>
class  SubscriptionType
    : public ModelBase
{
public:
    SubscriptionType();
    virtual ~SubscriptionType();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// SubscriptionType members


protected:
};

}
}
}
}

#endif /* SubscriptionType_H_ */
