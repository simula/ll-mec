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


#include "S1BearerSubscriptionCriteria.h"

namespace org {
namespace openapitools {
namespace server {
namespace model {

S1BearerSubscriptionCriteria::S1BearerSubscriptionCriteria()
{
    m_AssociateIdIsSet = false;
    m_PlmnIsSet = false;
    m_CellIdIsSet = false;
    m_ErabId = 0;
    m_ErabIdIsSet = false;
    
}

S1BearerSubscriptionCriteria::~S1BearerSubscriptionCriteria()
{
}

void S1BearerSubscriptionCriteria::validate()
{
    // TODO: implement validation
}

nlohmann::json S1BearerSubscriptionCriteria::toJson() const
{
    nlohmann::json val = nlohmann::json::object();

    if(m_AssociateIdIsSet)
    {
        val["associateId"] = ModelBase::toJson(m_AssociateId);
    }
    if(m_PlmnIsSet)
    {
        val["plmn"] = ModelBase::toJson(m_Plmn);
    }
    {
        nlohmann::json jsonArray;
        for( const auto& item : m_CellId )
        {
            jsonArray.push_back(ModelBase::toJson(item));
        }
        
        if(jsonArray.size() > 0)
        {
            val["cellId"] = jsonArray;
        } 
    }
    if(m_ErabIdIsSet)
    {
        val["erabId"] = m_ErabId;
    }
    

    return val;
}

void S1BearerSubscriptionCriteria::fromJson(const nlohmann::json& val)
{
    if(val.find("associateId") != val.end())
    {
        if(!val["associateId"].is_null())
        {
            AssociateId newItem;
            newItem.fromJson(val["associateId"]);
            setAssociateId( newItem );
        }
        
    }
    if(val.find("plmn") != val.end())
    {
        if(!val["plmn"].is_null())
        {
            Plmn newItem;
            newItem.fromJson(val["plmn"]);
            setPlmn( newItem );
        }
        
    }
    {
        m_CellId.clear();
        if(val.find("cellId") != val.end())
        {
            for( const auto& item : val["cellId"] )
            {
                
                if(item.is_null())
                {
                    m_CellId.push_back( std::string() );
                }
                else
                {
                    std::string newItem;
                    newItem.fromJson(item);
                    m_CellId.push_back( newItem );
                }
                
            }
        }
    }
    if(val.find("erabId") != val.end())
    {
        setErabId(val.at("erabId"));
    }
    
}


AssociateId S1BearerSubscriptionCriteria::getAssociateId() const
{
    return m_AssociateId;
}
void S1BearerSubscriptionCriteria::setAssociateId(AssociateId const& value)
{
    m_AssociateId = value;
    m_AssociateIdIsSet = true;
}
bool S1BearerSubscriptionCriteria::associateIdIsSet() const
{
    return m_AssociateIdIsSet;
}
void S1BearerSubscriptionCriteria::unsetAssociateId()
{
    m_AssociateIdIsSet = false;
}
Plmn S1BearerSubscriptionCriteria::getPlmn() const
{
    return m_Plmn;
}
void S1BearerSubscriptionCriteria::setPlmn(Plmn const& value)
{
    m_Plmn = value;
    m_PlmnIsSet = true;
}
bool S1BearerSubscriptionCriteria::plmnIsSet() const
{
    return m_PlmnIsSet;
}
void S1BearerSubscriptionCriteria::unsetPlmn()
{
    m_PlmnIsSet = false;
}
std::vector<std::string>& S1BearerSubscriptionCriteria::getCellId()
{
    return m_CellId;
}
bool S1BearerSubscriptionCriteria::cellIdIsSet() const
{
    return m_CellIdIsSet;
}
void S1BearerSubscriptionCriteria::unsetCellId()
{
    m_CellIdIsSet = false;
}
int32_t S1BearerSubscriptionCriteria::getErabId() const
{
    return m_ErabId;
}
void S1BearerSubscriptionCriteria::setErabId(int32_t const value)
{
    m_ErabId = value;
    m_ErabIdIsSet = true;
}
bool S1BearerSubscriptionCriteria::erabIdIsSet() const
{
    return m_ErabIdIsSet;
}
void S1BearerSubscriptionCriteria::unsetErabId()
{
    m_ErabIdIsSet = false;
}

}
}
}
}

