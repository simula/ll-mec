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
 * BwInfo.h
 *
 * information of bandwidth resource
 */

#ifndef BwInfo_H_
#define BwInfo_H_


#include "ModelBase.h"

#include "FixedBWPriority.h"
#include <string>
#include "AllocationDirection.h"
#include "RequestType.h"
#include "SessionFilterElement.h"
#include <vector>
#include "TimeStamp.h"

namespace org {
namespace llmec {
namespace mp2 {
namespace model {

/// <summary>
/// information of bandwidth resource
/// </summary>
class  BwInfo
    : public ModelBase
{
public:
    BwInfo();
    virtual ~BwInfo();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// BwInfo members

    /// <summary>
    /// 
    /// </summary>
    TimeStamp getTimeStamp() const;
    void setTimeStamp(TimeStamp const& value);
    bool timeStampIsSet() const;
    void unsetTimeStamp();
    /// <summary>
    /// Application instance identifier
    /// </summary>
    std::string getAppInsId() const;
    void setAppInsId(std::string const& value);
        /// <summary>
    /// 
    /// </summary>
    RequestType getRequestType() const;
    void setRequestType(RequestType const& value);
        /// <summary>
    /// Session filtering criteria, applicable when requestType is set as SESSION_SPECIFIC_BW_ALLOCATION. Any filtering criteria shall define a single session only. In case multiple sessions match sessionFilter the request shall be rejected
    /// </summary>
    std::vector<SessionFilterElement>& getSessionFilter();
    bool sessionFilterIsSet() const;
    void unsetSessionFilter();
    /// <summary>
    /// 
    /// </summary>
    FixedBWPriority getFixedBWPriority() const;
    void setFixedBWPriority(FixedBWPriority const& value);
    bool fixedBWPriorityIsSet() const;
    void unsetFixedBWPriority();
    /// <summary>
    /// Size of requested fixed BW allocation in [bps]
    /// </summary>
    std::string getFixedAllocation() const;
    void setFixedAllocation(std::string const& value);
        /// <summary>
    /// 
    /// </summary>
    AllocationDirection getAllocationDirection() const;
    void setAllocationDirection(AllocationDirection const& value);
    
protected:
    TimeStamp m_TimeStamp;
    bool m_TimeStampIsSet;
    std::string m_AppInsId;

    RequestType m_RequestType;

    std::vector<SessionFilterElement> m_SessionFilter;
    bool m_SessionFilterIsSet;
    FixedBWPriority m_FixedBWPriority;
    bool m_FixedBWPriorityIsSet;
    std::string m_FixedAllocation;

    AllocationDirection m_AllocationDirection;

};

}
}
}
}

#endif /* BwInfo_H_ */
