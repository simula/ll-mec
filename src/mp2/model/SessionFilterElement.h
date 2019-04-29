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
 * SessionFilterElement.h
 *
 * 
 */

#ifndef SessionFilterElement_H_
#define SessionFilterElement_H_


#include "ModelBase.h"

#include <string>
#include <vector>

namespace org {
namespace llmec {
namespace mp2 {
namespace model {

/// <summary>
/// 
/// </summary>
class  SessionFilterElement
    : public ModelBase
{
public:
    SessionFilterElement();
    virtual ~SessionFilterElement();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& json) override;

    /////////////////////////////////////////////
    /// SessionFilterElement members

    /// <summary>
    /// Source address identity of session (including range)
    /// </summary>
    std::string getSourceIp() const;
    void setSourceIp(std::string const& value);
    bool sourceIpIsSet() const;
    void unsetSourceIp();
    /// <summary>
    /// Source port identity of session 
    /// </summary>
    std::vector<std::string>& getSourcePort();
    bool sourcePortIsSet() const;
    void unsetSourcePort();
    /// <summary>
    /// Destination address identity of session (including range)
    /// </summary>
    std::string getDstAddress() const;
    void setDstAddress(std::string const& value);
    bool dstAddressIsSet() const;
    void unsetDstAddress();
    /// <summary>
    /// Destination port identity of session 
    /// </summary>
    std::vector<std::string>& getDstPort();
    bool dstPortIsSet() const;
    void unsetDstPort();
    /// <summary>
    /// Protocol number
    /// </summary>
    std::string getProtocol() const;
    void setProtocol(std::string const& value);
    bool protocolIsSet() const;
    void unsetProtocol();

protected:
    std::string m_SourceIp;
    bool m_SourceIpIsSet;
    std::vector<std::string> m_SourcePort;
    bool m_SourcePortIsSet;
    std::string m_DstAddress;
    bool m_DstAddressIsSet;
    std::vector<std::string> m_DstPort;
    bool m_DstPortIsSet;
    std::string m_Protocol;
    bool m_ProtocolIsSet;
};

}
}
}
}

#endif /* SessionFilterElement_H_ */
