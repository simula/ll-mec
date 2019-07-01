/*
 * Copyright 2016-2018 Eurecom and Mosaic5G Platforms Authors
 * Licensed to the Mosaic5G under one or more contributor license
 * agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership.
 * The Mosaic5G licenses this file to You under the
 * Apache License, Version 2.0  (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the Mosaic5G:
 *  	contact@mosaic5g.io
 */

/*!
  \file rib.h
  \brief header file of rib.cpp stores RAN Information Base from FlexRAN controllers
  \author Tien-Thinh NGUYEN
  \company Eurecom
  \email: thinhnt1983@gmail.com
*/


#ifndef RIB_H_
#define RIB_H_

#include <map>
#include <set>

#include <memory>
#include <set>
#include <chrono>
#include <mutex>
#include <utility>
#include "json.h"
#include <unistd.h>
enum APP_TYPE_t {
  APP_PLMN_INFO  = 0,
  APP_RAB_INFO   = 1
};

namespace llmec {
namespace mp1 {

namespace rib {



class Rib {
public:
    /*
     * Update ue's info
     * @param [imsi] UE's imsi
     * @param [ueInfo] UE's info
     */
	bool update_ue_info(std::string imsi, nlohmann::json ueInfo);
    /*
     * Update ue's info
     * @param [eNBId] eNB's Id
     * @param [eNBInfo] eNB's info
     */
	bool update_eNB_info(uint64_t eNBId, nlohmann::json eNBInfo);

    /*
     * Get PLMN info from DB
     * @param [appInsId] list of appInsIds
     * @return PLMN info in Json format
     */
	nlohmann::json get_plmn_info(const std::vector<std::string> &appInsIds);

	bool getAppPermission(std::string appId, APP_TYPE_t appType);



private:
	std::map<uint64_t, nlohmann::json> eNBInfos;
	std::map<std::string, nlohmann::json> ueInfos;
    mutable std::mutex ue_info_mutex;
    mutable std::mutex eNB_info_mutex;
    std::map<std::pair<std::string, APP_TYPE_t>, bool> appAuthorization; //test authentication

};

}

}
}
#endif
