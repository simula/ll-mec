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
 * Self.h
 *
 * Self-referring URI.
 */

#ifndef Self_H_
#define Self_H_


#include "LinkType.h"
#include "json.h"

namespace llmec {
namespace mp1 {
namespace model {

/// <summary>
/// Self-referring URI.
/// </summary>
class  Self
{
public:
    Self();
    virtual ~Self();

    void validate();

    /////////////////////////////////////////////
    /// Self members

    /// <summary>
    /// 
    /// </summary>
    LinkType getSelf() const;
    void setSelf(LinkType const& value);
    
    friend void to_json(nlohmann::json& j, const Self& o);
    friend void from_json(const nlohmann::json& j, Self& o);
protected:
    LinkType m_Self;

};

}
}
}

#endif /* Self_H_ */
