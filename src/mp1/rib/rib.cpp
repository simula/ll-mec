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
  \file rib.cpp
  \brief rib stores RAN Information Base from FlexRAN controllers
  \author Tien-Thinh NGUYEN
  \company Eurecom
  \email: thinhnt1983@gmail.com
*/

#include "rib.h"
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include "spdlog.h"
#include <iostream>

namespace llmec {
namespace mp1 {
namespace rib {

bool Rib::update_ue_info(std::string imsi, nlohmann::json ueInfo){
	std::map<std::string, nlohmann::json>::iterator it;
	it = ueInfos.find(imsi);
	if (it != ueInfos.end()){ //if existed->update info
		ue_info_mutex.lock();
		it->second = ueInfo;
		ue_info_mutex.unlock();
		spdlog::get("ll-mec")->debug("[RIB] Updated UE IMSI {}", imsi);
		spdlog::get("ll-mec")->debug("[RIB] UE's Info:\n {}", (it->second).dump());
	} else{//add to the map
		ue_info_mutex.lock();
		ueInfos.insert(std::pair<std::string, nlohmann::json> (imsi, ueInfo));
		ue_info_mutex.unlock();
		spdlog::get("ll-mec")->info("[RIB] Added UE IMSI {}", imsi);
		spdlog::get("ll-mec")->debug("[RIB] UE's Info:\n {}", ueInfo.dump());
	}
	return true;
}
bool Rib::update_eNB_info(uint64_t eNBId, nlohmann::json eNBInfo){
	std::map<uint64_t, nlohmann::json>::iterator it;
	it = eNBInfos.find(eNBId);
	if (it != eNBInfos.end()){ //if existed->update info
		eNB_info_mutex.lock();
		it->second = eNBInfo;
		eNB_info_mutex.unlock();
		spdlog::get("ll-mec")->info("[RIB] Updated eNB Id {}", eNBId);
	} else{//add to the map
		eNB_info_mutex.lock();
		eNBInfos.insert(std::pair<uint64_t, nlohmann::json> (eNBId, eNBInfo));
		eNB_info_mutex.unlock();
		spdlog::get("ll-mec")->info("[RIB] Added eNB Id {}", eNBId);
	}
	return true;
}

nlohmann::json Rib::get_plmn_info(const std::vector<std::string> &appInsIds){
	spdlog::get("ll-mec")->info("[RIB] Get PLMN info");
	nlohmann::json plmnInfo;
	std::map<uint64_t, nlohmann::json>::iterator it;

	for (auto it = ueInfos.begin(); it != ueInfos.end(); ++it){
		/*
		int numUEConfig = (it->second).size();
		for (int i = 0; i < numUEConfig; ++i){
			std::string imsi = (((it->second).at(i))["imsi"]).get<std::string>().c_str();
			try{
				plmnInfo["mcc"] = imsi.substr(0,3);
				plmnInfo["mnc"] = imsi.substr(3,2);
			} catch (const std::out_of_range& oor) {
				spdlog::get("ll-mec")->warn("[RIB] Could not get MCC, MNC from IMSI, use default values");
				plmnInfo["mcc"] = "294";
				plmnInfo["mnc"] = "84";
			}

			spdlog::get("ll-mec")->info("[RIB] Get PLMN info, MCC {}", plmnInfo["mcc"].get<std::string>().c_str());
			spdlog::get("ll-mec")->info("[RIB] Get PLMN info, MNC {}", plmnInfo["mnc"].get<std::string>().c_str());
		}
		*/

		std::string imsi = ((it->second)["imsi"]).get<std::string>().c_str();
		try{
			plmnInfo["mcc"] = imsi.substr(0,3);
			plmnInfo["mnc"] = imsi.substr(3,2);
		} catch (const std::out_of_range& oor) {
			spdlog::get("ll-mec")->warn("[RIB] Could not get MCC, MNC from IMSI, use default values");
			//plmnInfo["mcc"] = "294";
			//plmnInfo["mnc"] = "84";
		}

		spdlog::get("ll-mec")->info("[RIB] Get PLMN info, MCC {}", plmnInfo["mcc"].get<std::string>().c_str());
		spdlog::get("ll-mec")->info("[RIB] Get PLMN info, MNC {}", plmnInfo["mnc"].get<std::string>().c_str());


	}

	for (auto it = eNBInfos.begin(); it != eNBInfos.end(); ++it){
		plmnInfo["cellId"] = {};
		int numCellId = (it->second).size();
		for (int i = 0; i < numCellId; ++i){
			int cellId = ((it->second).at(i))["phyCellId"].get<int>(); //TODO: cellID or PhyCellID
			spdlog::get("ll-mec")->debug("[RIB] Get PLMN info, CellId {}", cellId);
			plmnInfo["cellId"].push_back(std::to_string(cellId));
		}

	}
	return plmnInfo;

}

bool Rib::get_app_permission(std::string appId, llmec::app::uplane::ueEventType appType){
	//always return true for the moment
	return true;
}

void Rib::update_app_subscription_info(std::string appId, llmec::app::uplane::ueEventType appType, nlohmann::json subscriptionInfo){

	std::map<std::pair<std::string, llmec::app::uplane::ueEventType>, nlohmann::json>::iterator it;
	it  = appSubscriptionList.find(std::make_pair(appId,appType));
	//if not present -> create a new one
	if (it == appSubscriptionList.end()){
		appSubscriptionList.emplace(std::make_pair(appId,appType), subscriptionInfo);
	} else{ //if existed-> simply update
		it->second = subscriptionInfo;
	}

}

nlohmann::json Rib::get_app_subscription_info(std::string appId, llmec::app::uplane::ueEventType appType){
	std::map<std::pair<std::string, llmec::app::uplane::ueEventType>, nlohmann::json>::iterator it;
	it  = appSubscriptionList.find(std::make_pair(appId,appType));
	//if not present -> create a new one
	if (it != appSubscriptionList.end()){
		return it->second;
	} else{ //if existed-> simply update
		return nlohmann::json();
	}

}

nlohmann::json Rib::get_app_subscription_list(llmec::app::uplane::ueEventType appType){
	//std::string appId
	nlohmann::json subscriptionList;
	subscriptionList["links"] = mp1_server_url;//store server url for the moment, should be updated with base+path for this appType

	for (auto it : appSubscriptionList){
		nlohmann::json subscriptionInfo;
		if (it.first.second == appType){
			subscriptionInfo["SubscriptionType"] = appType;
			subscriptionInfo["href"] = ((it.second)["callbackReference"]).get<std::string>().c_str();
		}
		subscriptionList["subscription"].push_back(subscriptionInfo);
	}
	return subscriptionList;

}


nlohmann::json Rib::get_app_subscription_list(){
	//std::string appId
	nlohmann::json subscriptionList;
	subscriptionList["links"] = mp1_server_url;//store server url for the moment, should be updated with base+path for this appType

	for (auto it : appSubscriptionList){
		nlohmann::json subscriptionInfo;
		subscriptionInfo["SubscriptionType"] = (it.first).second;
		subscriptionInfo["href"] = ((it.second)["callbackReference"]).get<std::string>().c_str();
		subscriptionList["subscription"].push_back(subscriptionInfo);
	}
	return subscriptionList;

}



void Rib::delete_app_subscription_info(std::string appId, llmec::app::uplane::ueEventType appType){
	//std::map<std::pair<std::string, llmec::app::uplane::ueEventType>, nlohmann::json>::iterator it;
	appSubscriptionList.erase(std::make_pair(appId,appType));
	//appSubscriptionList.erase(it);
}

void Rib::set_mp1_server_url(std::string url){
	mp1_server_url = url;
	spdlog::get("ll-mec")->debug("[RIB] Server URL: {}", url);
}

std::string Rib::get_mp1_server_url(){
	return mp1_server_url;
}

/*
std::vector<std::pair<std::string, std::string>> Rib::get_callback_reference(std::string imsi, llmec::app::uplane::ueEventType evType){
	std::vector<std::pair<std::string, std::string>> result;
	std::map<std::pair<std::string, llmec::app::uplane::ueEventType>, nlohmann::json>::iterator it;
	for (it = subscriptionList.begin(); it!= subscriptionList.end(); it++){
		if (it->first.second == evType){
			spdlog::get("ll-mec")->debug("[RIB] get_callback_reference: appInsId {}", ((it->second)["filterCriteria"]["appInsId"]).get<std::string>().c_str());
			spdlog::get("ll-mec")->debug("[RIB] get_callback_reference: callbackReference {}", ((it->second)["callbackReference"]).get<std::string>().c_str());
			//TODO: check filterCriteria e.g., based on AssociatedId (type=1, UE_IPVv4_ADDR)
			std::pair<std::string, std::string> appPair = std::make_pair(((it->second)["filterCriteria"]["appInsId"]).get<std::string>().c_str(), ((it->second)["callbackReference"]).get<std::string>().c_str());
			result.push_back(appPair);
		}
	}
	return result;
}
*/

nlohmann::json Rib::get_notification_info(std::string imsi, llmec::app::uplane::ueEventType evType){
	nlohmann::json notificationInfos;
	nlohmann::json ueInfo = ueInfos[imsi];
	std::map<std::pair<std::string, llmec::app::uplane::ueEventType>, nlohmann::json>::iterator it;
	for (it = appSubscriptionList.begin(); it!= appSubscriptionList.end(); it++){
		if (it->first.second == evType){
			nlohmann::json appInfo = it->second;
			nlohmann::json notificationInfo;
			notificationInfo["appInsId"] = ((it->second)["filterCriteria"]["appInsId"]).get<std::string>().c_str();
			notificationInfo["callbackReference"] =  (appInfo["callbackReference"]).get<std::string>().c_str();
			spdlog::get("ll-mec")->debug("[RIB] get_callback_reference: appInsId {}", (appInfo["filterCriteria"]["appInsId"]).get<std::string>().c_str());
			spdlog::get("ll-mec")->debug("[RIB] get_callback_reference: callbackReference {}", (appInfo["callbackReference"]).get<std::string>().c_str());
			//TODO: check filterCriteria e.g., based on AssociatedId (type=1, UE_IPVv4_ADDR)

			switch (evType){
			case llmec::app::uplane::UE_EVENT_RAB_ESTABLISHMENT:
				notificationInfo["notificationInfo"]["ecgi"]["mcc"] = imsi.substr(0,3);
				notificationInfo["notificationInfo"]["ecgi"]["mnc"] = imsi.substr(3,2);
				notificationInfo["notificationInfo"]["ecgi"]["cellId"] = "123";//need to get from eNB's Info
				notificationInfo["notificationInfo"]["associateId"]["type"] = 1; //hardcoded for the moment
				notificationInfo["notificationInfo"]["associateId"]["value"] = "172.0.0.2"; //hardcoded for the moment (should be updated from MP2)
				notificationInfo["notificationInfo"]["erabId"] = 4; //hardcoded
				notificationInfo["notificationInfo"]["timeStamp"]["seconds"] = 1577836800; //hardcoded
				notificationInfo["notificationInfo"]["timeStamp"]["nanoSeconds"] = 0; //hardcoded
				notificationInfo["notificationInfo"]["erabQosParameters"]["qosInformation"]["erabMbrDl"] = 0;//hardcoded
				notificationInfo["notificationInfo"]["erabQosParameters"]["qosInformation"]["erabMbrUl"] = 0;//hardcoded
				notificationInfo["notificationInfo"]["erabQosParameters"]["qosInformation"]["erabGbrDl"] = 0;//hardcoded
				notificationInfo["notificationInfo"]["erabQosParameters"]["qosInformation"]["erabGbrUl"] = 0;//hardcoded
				notificationInfo["notificationInfo"]["erabQosParameters"]["qci"] = 0;//hardcoded
				notificationInfo["notificationInfo"]["tempUeId"]["mmec"] = "mmec"; //hardcoded
				notificationInfo["notificationInfo"]["tempUeId"]["mtmsi"] = "mtmsi";//hardcoded
				break;
			case llmec::app::uplane::UE_EVENT_CELL_CHANGE:
				break;
			default:
				break;
			}
			notificationInfos.push_back(notificationInfo);
		}
	}
	return notificationInfos;

}

}
}
}
