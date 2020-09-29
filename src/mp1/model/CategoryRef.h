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
 * CategoryRef.h
 *
 * This type represents the category reference
 */

#ifndef CategoryRef_H_
#define CategoryRef_H_


#include <string>
#include "json.h"

namespace llmec {
namespace mp1 {
namespace model {

/// <summary>
/// This type represents the category reference
/// </summary>
class  CategoryRef
{
public:
    CategoryRef();
    virtual ~CategoryRef();

    void validate();

    /////////////////////////////////////////////
    /// CategoryRef members

    /// <summary>
    /// Reference of the catalogue
    /// </summary>
    std::string getHref() const;
    void setHref(std::string const& value);
        /// <summary>
    /// Unique identifier of the category
    /// </summary>
    std::string getId() const;
    void setId(std::string const& value);
        /// <summary>
    /// Name of the category
    /// </summary>
    std::string getName() const;
    void setName(std::string const& value);
        /// <summary>
    /// Category version
    /// </summary>
    std::string getVersion() const;
    void setVersion(std::string const& value);
    
    friend void to_json(nlohmann::json& j, const CategoryRef& o);
    friend void from_json(const nlohmann::json& j, CategoryRef& o);
protected:
    std::string m_Href;

    std::string m_Id;

    std::string m_Name;

    std::string m_Version;

};

}
}
}

#endif /* CategoryRef_H_ */
