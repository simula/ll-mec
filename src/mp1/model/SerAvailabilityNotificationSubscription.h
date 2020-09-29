/**
* Mp1 API
* The ETSI MEC ISG MEC011 Application Enablement API described using OpenAPI
*
* The version of the OpenAPI document: 1.1.1
* Contact: cti_support@etsi.org
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/
/*
 * SerAvailabilityNotificationSubscription.h
 *
 * This type represents a subscription to the notifications from the mobile edge platform regarding the availability of a mobile edge service or a list of mobile edge services.
 */

#ifndef SerAvailabilityNotificationSubscription_H_
#define SerAvailabilityNotificationSubscription_H_


#include "Self.h"
#include "ServiceInfo.h"
#include <string>
#include "json.h"
#include "NotificationSubscription.h"

namespace llmec {
namespace mp1 {
namespace model {

/// <summary>
/// This type represents a subscription to the notifications from the mobile edge platform regarding the availability of a mobile edge service or a list of mobile edge services.
/// </summary>
class  SerAvailabilityNotificationSubscription : public NotificationSubscription
{
public:
    SerAvailabilityNotificationSubscription();
    virtual ~SerAvailabilityNotificationSubscription();
/*
    void validate();

    /////////////////////////////////////////////
    /// SerAvailabilityNotificationSubscription members

    /// <summary>
    /// Shall be set to SerAvailabilityNotificationSubscription.
    /// </summary>
    std::string getSubscriptionType() const;
    void setSubscriptionType(std::string const& value);
        /// <summary>
    /// URI selected by the mobile edge application instance to receive notifications on the subscribed mobile edge service availability information. This shall be included in both the request and the response.
    /// </summary>
    std::string getCallbackReference() const;
    void setCallbackReference(std::string const& value);
        /// <summary>
    /// 
    /// </summary>
    Self getLinks() const;
    void setLinks(Self const& value);
    */
        /// <summary>
    /// 
    /// </summary>
    ServiceInfo getFilteringCriteria() const;
    void setFilteringCriteria(ServiceInfo const& value);
    
    friend void to_json(nlohmann::json& j, const SerAvailabilityNotificationSubscription& o);
    friend void from_json(const nlohmann::json& j, SerAvailabilityNotificationSubscription& o);
protected:
/*    std::string m_SubscriptionType;

    std::string m_CallbackReference;

    Self m__links;
*/
    ServiceInfo m_FilteringCriteria;

};

}
}
}

#endif /* SerAvailabilityNotificationSubscription_H_ */
