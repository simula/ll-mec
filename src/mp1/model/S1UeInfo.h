/**
* MP1 API
* The ETSI MEC ISG MEC012 Radio Network Information API, AND The ETSI MEC ISG MEC011 Application Enablement API
* AND some additional MEC APIs described using OpenAPI
*
* The version of the OpenAPI document: 1.1.1
* 
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/
/*
 * S1UeInfo.h
 *
 * The information on users per cell.
 */

#ifndef S1UeInfo_H_
#define S1UeInfo_H_


#include "Ecgi.h"
#include "TempUeId.h"
#include "S1BearerInfoDetailed.h"
#include "AssociateId.h"
#include <vector>
#include "json.h"

namespace llmec {
namespace mp1 {
namespace model {

/// <summary>
/// The information on users per cell.
/// </summary>
class  S1UeInfo
{
public:
    S1UeInfo();
    virtual ~S1UeInfo();

    void validate();

    /////////////////////////////////////////////
    /// S1UeInfo members

    /// <summary>
    /// 
    /// </summary>
    std::vector<TempUeId>& getTempUeId();
        /// <summary>
    /// 
    /// </summary>
    std::vector<AssociateId>& getAssociateId();
    bool associateIdIsSet() const;
    void unsetAssociateId();
    /// <summary>
    /// 
    /// </summary>
    std::vector<Ecgi>& getEcgi();
        /// <summary>
    /// 
    /// </summary>
    std::vector<S1BearerInfoDetailed>& getS1BearerInfoDetailed();
    
    friend void to_json(nlohmann::json& j, const S1UeInfo& o);
    friend void from_json(const nlohmann::json& j, S1UeInfo& o);
protected:
    std::vector<TempUeId> m_TempUeId;

    std::vector<AssociateId> m_AssociateId;
    bool m_AssociateIdIsSet;
    std::vector<Ecgi> m_Ecgi;

    std::vector<S1BearerInfoDetailed> m_S1BearerInfoDetailed;

};

}
}
}

#endif /* S1UeInfo_H_ */
