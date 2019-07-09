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
#include "ModelBase.h"
#include "ue_event.h"

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

    /*
     * Get MEC APP permission
     * @param [appInsId] AppId
     * @param [appType] type of subscription/query
     * @return true if this app has permission to get information of this type. if not return false
     */
	bool get_app_permission(std::string appId, llmec::app::uplane::ueEventType appType);

	/*
     * Update app's subscription info
     * @param [appInsId] AppId
     * @param [appType] type of subscription/query
     * @param [subscriptionInfo] subscription info
     */
	void update_app_subscription_info(std::string appId, llmec::app::uplane::ueEventType appType, nlohmann::json subscriptionInfo);

	/*
     * Get app's subscription info
     * @param [appInsId] AppId
     * @param [appType] type of subscription/query
     * @return App's subscription info
     */
	nlohmann::json get_app_subscription_info(std::string appId, llmec::app::uplane::ueEventType appType);

	/*
     * Set url of MP1 server (to be included in the response to App subscription request)
     * @param [url] url in which MP1 server is listening to
     */
	void set_mp1_server_url(std::string url);

	/*
     * Get url of MP1 server
     * @return url in which MP1 server is listening to
     */
	std::string get_mp1_server_url();

	/*
     * Get information to be notified to the corresponding app event (e.g., RAB establishment)
     * @param [imsi] UE's IMSI
     * @param [appType] type of subscription/query
     * @return notification info e.g., RabEstNotification
     */
	nlohmann::json get_notification_info(std::string imsi, llmec::app::uplane::ueEventType evType);

private:
	mutable std::mutex eNB_info_mutex;
	std::map<uint64_t, nlohmann::json> eNBInfos;
    mutable std::mutex ue_info_mutex;
	std::map<std::string, nlohmann::json> ueInfos;

    mutable std::mutex app_subscription_mutex;
    // list of MEC apps subscribed to MEC platform
    std::map<std::pair<std::string, llmec::app::uplane::ueEventType>, nlohmann::json> appSubscriptionList;
    //MP1's URL
    std::string mp1_server_url;

};

}

}
}
#endif
