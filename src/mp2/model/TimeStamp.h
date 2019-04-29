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
 * TimeStamp.h
 *
 * 
 */

#ifndef TimeStamp_H_
#define TimeStamp_H_


#include "ModelBase.h"


namespace org {
namespace llmec {
namespace mp2 {
namespace model {

/// <summary>
/// 
/// </summary>
class  TimeStamp
    : public ModelBase
{
public:
    TimeStamp();
    virtual ~TimeStamp();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// TimeStamp members

    /// <summary>
    /// The seconds part of the Time. Time is defined as Unix-time since January 1, 1970, 00:00:00 UTC
    /// </summary>
    int32_t getSeconds() const;
    void setSeconds(int32_t const value);
        /// <summary>
    /// The nanoseconds part of the Time. Time is defined as Unix-time since January 1, 1970, 00:00:00 UTC
    /// </summary>
    int32_t getNanoSeconds() const;
    void setNanoSeconds(int32_t const value);
    
protected:
    int32_t m_Seconds;

    int32_t m_NanoSeconds;

};

}
}
}
}

#endif /* TimeStamp_H_ */
