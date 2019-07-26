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

nlohmann::json Rib::get_plmn_info(const std::string appInsId){
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
			plmnInfo["plmn"]["mcc"] = imsi.substr(0,3);
			plmnInfo["plmn"]["mnc"] = imsi.substr(3,2);
		} catch (const std::out_of_range& oor) {
			spdlog::get("ll-mec")->warn("[RIB] Could not get MCC, MNC from IMSI, use default values");
			//plmnInfo["mcc"] = "294";
			//plmnInfo["mnc"] = "84";
		}
		spdlog::get("ll-mec")->info("[RIB] Get PLMN info, MCC {}", plmnInfo["plmn"]["mcc"].get<std::string>().c_str());
		spdlog::get("ll-mec")->info("[RIB] Get PLMN info, MNC {}", plmnInfo["plmn"]["mnc"].get<std::string>().c_str());

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

	nlohmann::json subscriptionList;

	for (auto it : appSubscriptionList){
		nlohmann::json subscriptionInfo;
		if (it.first.second == appType){
			subscriptionInfo["SubscriptionType"] = appType;
			subscriptionInfo["href"] = ((it.second)["callbackReference"]).get<std::string>().c_str();
			subscriptionList["subscription"].push_back(subscriptionInfo);
			subscriptionList["links"] = mp1_server_url;//store server url for the moment, should be updated with base+path for this appType
		}
	}
	return subscriptionList;
}

nlohmann::json Rib::get_app_subscription_list(){
	spdlog::get("ll-mec")->debug("[RIB] Get a list of all subscriptions");
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
	spdlog::get("ll-mec")->debug("[RIB] Get notification info");
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

llmec::mp1::model::ServiceInfo Rib::get_service_info_by_id(std::string serInstanceId){

	std::map<std::string, llmec::mp1::model::ServiceInfo>::iterator it;
	it  = serviceInfoList.find(serInstanceId);

	if (it != serviceInfoList.end()){
		return it->second;
	} else{
		spdlog::get("ll-mec")->info("[RIB::get_service_info] No service with this serInstanceId {}",serInstanceId);
		return llmec::mp1::model::ServiceInfo();
	}
}

llmec::mp1::model::ServiceInfo Rib::get_service_info_by_name(std::string serName){
	spdlog::get("ll-mec")->debug("[RIB] Get service info by name ({})",serName);
	for (auto it : serviceInfoList){
		llmec::mp1::model::ServiceInfo serviceInfo = it.second;
		if (serviceInfo.getSerName() == serName) return it.second;
	}
	return llmec::mp1::model::ServiceInfo();
}

std::vector<llmec::mp1::model::ServiceInfo> Rib::get_service_info_by_category(std::string serCategory){
	spdlog::get("ll-mec")->debug("[RIB] Get service info by category ({})",serCategory);
	std::vector<llmec::mp1::model::ServiceInfo> serviceInfos;
	for (auto it : serviceInfoList){
		llmec::mp1::model::ServiceInfo serviceInfo = it.second;
		if (serviceInfo.getSerCategory().getId() == serCategory) serviceInfos.push_back(it.second);
	}
	return serviceInfos;
}


std::string Rib::update_service_info(const std::string serInstanceId, const llmec::mp1::model::ServiceInfo &serviceInfo){
	spdlog::get("ll-mec")->debug("[RIB] Update service info");
	if (serInstanceId.compare("") !=0 ){ //with a valid appInstanceId
		std::map<std::string, llmec::mp1::model::ServiceInfo>::iterator it;
		it  = serviceInfoList.find(serInstanceId);

		//update if existed
		if (it != serviceInfoList.end()){
			it->second = serviceInfo;
			spdlog::get("ll-mec")->debug("[RIB] Updated service info with serInstanceId {}",serInstanceId);
		} else { //if not existed, add to the list
			spdlog::get("ll-mec")->debug("[RIB] Added service info with serInstanceId {} to the list ",serInstanceId);
			serviceInfoList.emplace(serInstanceId, serviceInfo);
		}
		return serInstanceId;
	} else{ //generate a new appInstanceId and add to the list
		std::string newId = "serviceId"+std::to_string(serviceInfoList.size() + 1);
		spdlog::get("ll-mec")->debug("[RIB] Update service info, generate a new instance id {} and add to the list", newId);
		llmec::mp1::model::ServiceInfo temp;
		temp.setSerInstanceId(newId);
		temp.setSerName(serviceInfo.getSerName());
		temp.setSerCategory(serviceInfo.getSerCategory());
		temp.setVersion(serviceInfo.getVersion());
		temp.setState(serviceInfo.getState());
		temp.setTransportInfo(serviceInfo.getTransportInfo());
		temp.setSerializer(serviceInfo.getSerializer());

		serviceInfoList.emplace(newId, temp);
		return newId;
	}

}
void Rib::init_service_info(){
	spdlog::get("ll-mec")->debug("[RIB] Initialize list of default services");
	nlohmann::json serviceInfoPlmn, serviceInfoSubscription;
	nlohmann::json address;
	std::string serInstanceId;

	//PLMN info
	serInstanceId = "serviceId1";
	serviceInfoPlmn["serInstanceId"] = serInstanceId;
	serviceInfoPlmn["serName"] = "PLMN_Information";
	serviceInfoPlmn["serCategory"]["href"] = "catRNI";
	serviceInfoPlmn["serCategory"]["id"] = "RNI";
	serviceInfoPlmn["serCategory"]["name"] = "RNI";
	serviceInfoPlmn["serCategory"]["version"] = "version1";
	serviceInfoPlmn["version"] = "ServiceVersion1";
	serviceInfoPlmn["state"] = "ACTIVE";
	serviceInfoPlmn["transportInfo"]["id"] = "TransId1";
	serviceInfoPlmn["transportInfo"]["name"] = "REST";
	serviceInfoPlmn["transportInfo"]["description"] = "REST API";
	serviceInfoPlmn["transportInfo"]["type"] = "REST_HTTP";
	serviceInfoPlmn["transportInfo"]["protocol"] = "HTTP";
	serviceInfoPlmn["transportInfo"]["version"] = "2.0";
	serviceInfoPlmn["transportInfo"]["endpoint"]["uris"] = {"mp1/v1/queries/plmn_info"};
	serviceInfoPlmn["transportInfo"]["endpoint"]["addresses"] = {};
	address["host"] = "127.0.0.1";
	address["port"] = 8888;
	serviceInfoPlmn["transportInfo"]["endpoint"]["addresses"].push_back(address);
	serviceInfoPlmn["transportInfo"]["security"]["oAuth2Info"]["grantTypes"] = {"OAUTH2_CLIENT_CREDENTIALS"};
	serviceInfoPlmn["transportInfo"]["security"]["oAuth2Info"]["tokenEndpoint"] = "/mp1/v1/security/TokenEndPoint";
	serviceInfoPlmn["serializer"] = "JSON";

	llmec::mp1::model::ServiceInfo  servicePlmn;
	from_json(serviceInfoPlmn, servicePlmn);
	serviceInfoList.emplace(serInstanceId, servicePlmn);

	//RNI subscriptions
	serInstanceId = "serviceId2";
	serviceInfoPlmn["serInstanceId"] = serInstanceId;
	serviceInfoSubscription["serName"] = "Subscription";
	serviceInfoSubscription["serCategory"]["href"] = "catRNI";
	serviceInfoSubscription["serCategory"]["id"] = "RNI";
	serviceInfoSubscription["serCategory"]["name"] = "RNI";
	serviceInfoSubscription["serCategory"]["version"] = "version1";
	serviceInfoSubscription["version"] = "ServiceVersion1";
	serviceInfoSubscription["state"] = "ACTIVE";
	serviceInfoSubscription["transportInfo"]["id"] = "TransId2";
	serviceInfoSubscription["transportInfo"]["name"] = "REST";
	serviceInfoSubscription["transportInfo"]["description"] = "REST API";
	serviceInfoSubscription["transportInfo"]["type"] = "REST_HTTP";
	serviceInfoSubscription["transportInfo"]["protocol"] = "HTTP";
	serviceInfoSubscription["transportInfo"]["version"] = "2.0";
	serviceInfoSubscription["transportInfo"]["endpoint"]["uris"] = {"mp1/v1/rni/subscriptions"};
	serviceInfoSubscription["transportInfo"]["endpoint"]["addresses"] = {};
	address["host"] = "127.0.0.1";
	address["port"] = 8888;
	serviceInfoSubscription["transportInfo"]["endpoint"]["addresses"].push_back(address);
	serviceInfoSubscription["transportInfo"]["security"]["oAuth2Info"]["grantTypes"] = {"OAUTH2_CLIENT_CREDENTIALS"};
	serviceInfoSubscription["transportInfo"]["security"]["oAuth2Info"]["tokenEndpoint"] = "/mp1/v1/security/TokenEndPoint";
	serviceInfoSubscription["serializer"] = "JSON";

	llmec::mp1::model::ServiceInfo  serviceSubscription;
	from_json(serviceInfoSubscription, serviceSubscription);
	serviceInfoList.emplace(serInstanceId, serviceSubscription);

}
}
}
}
