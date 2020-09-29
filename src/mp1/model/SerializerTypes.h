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
 * SerializerTypes.h
 *
 * The enumeration SerializerTypes represents types of serializers
 */

#ifndef SerializerTypes_H_
#define SerializerTypes_H_


#include "json.h"

namespace llmec {
namespace mp1 {
namespace model {

/// <summary>
/// The enumeration SerializerTypes represents types of serializers
/// </summary>
class  SerializerTypes
{
public:
    SerializerTypes();
    virtual ~SerializerTypes();

    void validate();

    /////////////////////////////////////////////
    /// SerializerTypes members


    friend void to_json(nlohmann::json& j, const SerializerTypes& o);
    friend void from_json(const nlohmann::json& j, SerializerTypes& o);
protected:
};

}
}
}

#endif /* SerializerTypes_H_ */
