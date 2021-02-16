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
  \brief header file of rib.cpp stores RAN/MP1 Information Base from FlexRAN controllers
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
#include "ue_event.h"
#include "ServiceInfo.h"

namespace llmec {
namespace mp1 {
namespace rib {

//SubscriptionType of a meMp1Subscription (ETSI MEC 011)
typedef enum {
  ME_MP1_SUBSCRIPTION_SERVICE_AVAILABILITY = 0,
  ME_MP1_SUBSCRIPTION_APPLICATION_TERMINATION = 1,
} meMp1SubscriptionType;


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


	//For RNI API (ETSI MEC 012)

    /*
     * Get PLMN info from DB
     * @param [appInsId] App's ID
     * @return PLMN info in Json format
     */
	nlohmann::json get_plmn_info(const std::string appInsId);

    /*
     * Get TimeStamp
     * @param [appInsId] App's ID
     * @return PLMN info in Json format
     */
	//nlohmann::json get_timeStamp(const std::string appInsId);

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
    * Get list of Apps subscription info for a particular type
    * @param [appType] type of subscription/query
    * @return list of Apps subscription info
    */
	nlohmann::json get_app_subscription_list(llmec::app::uplane::ueEventType appType);

	/*
    * Get list of all app subscription
    * @return list of all app subscription
    */
	nlohmann::json get_app_subscription_list();


	/*
	 * Delete app's subscription from subscription list
	 * @param [appInsId] AppId
	 * @param [appType] type of subscription/query
	 */
	void delete_app_subscription_info(std::string appId, llmec::app::uplane::ueEventType appType);


	/*
     * Store address of MP1 server
     * @param [addr] address in which MP1 server is listening to
     */
	void set_mp1_server_addr(std::string addr);

	/*
     * Get IP address of MP1 server
     * @return IP address in which MP1 server is listening to
     */
	std::string get_mp1_server_addr();

	/*
     * Store Port of MP1 server
     * @param [port] port in which MP1 server is listening to
     */
	void set_mp1_server_port(int port);

	/*
     * Get port of MP1 server
     * @return port in which MP1 server is listening to
     */
	int get_mp1_server_port();


	/*
     * Get information to be notified to the corresponding RNI app event (e.g., RAB establishment)
     * @param [imsi] UE's IMSI
     * @param [appType] type of subscription/query
     * @return notification info e.g., RabEstNotification
     */
	nlohmann::json get_notification_info(std::string imsi, llmec::app::uplane::ueEventType evType);


	//for Services APIs (ETSI MEC 011)
	/*
     * Retrieve information of a service by its ID
     * @param [serInstanceId] Service's ID
     * @return service information
     */
	llmec::mp1::model::ServiceInfo get_service_info_by_id(std::string serInstanceId);

	/*
     * Retrieve information of a service by its name
     * @param [serName] Service's name
     * @return service information
     */
	llmec::mp1::model::ServiceInfo get_service_info_by_name(std::string serName);

	/*
     * Retrieve information of a list of service in a category
     * @param [serCategory] Service's name
     * @return a list of service with this category
     */
	std::vector<llmec::mp1::model::ServiceInfo> get_service_info_by_category(std::string serCategory);

	/*
     * Update the information about service if exist, if not create a new one and add to the list
     * @param [serInstanceId] Service's ID
     * @return service's ID
     */
	std::string update_service_info(const std::string serInstanceId, const llmec::mp1::model::ServiceInfo &serviceInfo);

	/*
     * Store default ME services into the list of services e.g., get PLMN, RNI subscription, etc.
     */
	void init_service_info();

	//serSubscription API

	/*
     * Update meMp1Subscription's info for a particular application instance
     * @param [appInstanceId] Application's Id of the subscriber
     * @param [subscriptionType] type of subscription (service availability/application termination)
     * @param [subscriptionId] ID of the subscription
     * @param [subscriptionInfo] subscription info
     */
	std::string update_me_mp1_subscription_info(std::string appInstanceId, meMp1SubscriptionType subscriptionType, nlohmann::json subscriptionInfo, std::string subscriptionId="");


	/*
     * Get meMp1Subscription's info for a particular application instance
     * @param [appInstanceId] Application's Id of the subscriber
     * @param [subscriptionType] type of subscription (service availability/application termination)
     * @param [subscriptionId] ID of the subscription
     * @return subscription info
     */
	nlohmann::json get_me_mp1_subscription_info(std::string appInstanceId, meMp1SubscriptionType subscriptionType, std::string subscriptionId);

	/*
     * Get a list of meMp1Subscription's info for a particular application instance
     * @param [appInstanceId] Application's Id of the subscriber
     * @return list of subscription info
     */
	nlohmann::json get_me_mp1_subscription_infos(std::string appInstanceId);

	/*
     * Delete a meMp1Subscription
     * @param [appInstanceId] Application's Id of the subscriber
     * @param [subscriptionType] type of subscription (service availability/application termination)
     * @param [subscriptionId] ID of the subscription
     *
     */
	void delete_me_mp1_subscription_info(std::string appInstanceId, meMp1SubscriptionType subscriptionType, std::string subscriptionId);

	/*
     * Get information to be notified to the corresponding ME App
     * @param [serviceInfo] ServiceInfo of the service which generates the event
     * @param [evType] type of subscription (AppTermination/ServiceAvailability)
     * @return notification info
     */
	nlohmann::json get_subscription_notification_info(nlohmann::json serviceInfo, meMp1SubscriptionType evType);


private:
	mutable std::mutex eNB_info_mutex;
	std::map<uint64_t, nlohmann::json> eNBInfos;
    mutable std::mutex ue_info_mutex;
	std::map<std::string, nlohmann::json> ueInfos;

    mutable std::mutex app_subscription_mutex;
    // list of MEC apps subscribed to MEC platform
    std::map<std::pair<std::string, llmec::app::uplane::ueEventType>, nlohmann::json> appSubscriptionList;
    //Address of MP1's server
    std::string mp1_server_addr;
    //Port of MP1's server
    int mp1_server_port;
    int subscription_id = 0;
    int service_id = 0;
    mutable std::mutex mp1_service_mutex;
    //list of service info for MEC ETSI 011
    std::map <std::string, llmec::mp1::model::ServiceInfo> serviceInfoList;
    mutable std::mutex mp1_subscription_mutex;
    //list of SerAvailabilityNotificationSubscriptions/AppTerminationNotificationSubscriptions for MEC ETSI 011
    std::map<std::pair<std::string, meMp1SubscriptionType>, std::map<std::string, nlohmann::json>> meMp1SubscriptionList;

};

}

}
}
#endif
