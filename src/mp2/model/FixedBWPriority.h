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
/*
 * FixedBWPriority.h
 *
 * Indicates the allocation priority when dealing with several applications or sessions in parallel. Values are not defined in the present document
 */

#ifndef FixedBWPriority_H_
#define FixedBWPriority_H_


#include "ModelBase.h"


namespace org {
namespace llmec {
namespace mp2 {
namespace model {

/// <summary>
/// Indicates the allocation priority when dealing with several applications or sessions in parallel. Values are not defined in the present document
/// </summary>
class  FixedBWPriority
    : public ModelBase
{
public:
    FixedBWPriority();
    virtual ~FixedBWPriority();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// FixedBWPriority members


protected:
};

}
}
}
}

#endif /* FixedBWPriority_H_ */
