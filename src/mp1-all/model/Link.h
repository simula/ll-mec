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
 * Link.h
 *
 * List of hyperlinks related to the resource
 */

#ifndef Link_H_
#define Link_H_


#include "ModelBase.h"

#include <string>

namespace org {
namespace openapitools {
namespace server {
namespace model {

/// <summary>
/// List of hyperlinks related to the resource
/// </summary>
class  Link
    : public ModelBase
{
public:
    Link();
    virtual ~Link();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// Link members

    /// <summary>
    /// URI referring to a resource
    /// </summary>
    std::string getSelf() const;
    void setSelf(std::string const& value);
    bool selfIsSet() const;
    void unsetSelf();

protected:
    std::string m_Self;
    bool m_SelfIsSet;
};

}
}
}
}

#endif /* Link_H_ */
