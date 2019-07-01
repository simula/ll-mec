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

bool Rib::getAppPermission(std::string appId, APP_TYPE_t appType){
/*
	 auto search =  appAuthorization.find(std::make_pair(appId,appType));
	 if (search != appAuthorization.end()){
		 return search->second;
	 } else {
		 return false;
	 }
	 */
	//always return true for the moment
	return true;
}

}
}
}
