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
  \file rib_updater.cpp
  \brief rib_updater update the RIB from FlexRAN controllers
  \author Tien-Thinh NGUYEN
  \company Eurecom
  \email: thinhnt1983@gmail.com
*/

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <sys/timerfd.h>
#include <curl/curl.h>
#include "rib_updater.h"
#include "spdlog.h"

#define DEFAULT_RIB_FILE  "src/mp1/inputs/mp1.json"
#define FLEXRAN_CURL_TIMEOUT_MS 100L
namespace llmec {
namespace mp1 {
namespace rib {

void rib_updater::run ()
{

	struct itimerspec its;
	int fd;
	struct timespec now;
	uint64_t exp;
	ssize_t s;

	spdlog::get("ll-mec")->debug("[RIB UPDATER] start timer");
	// Create a CLOCK_REALTIME absolute timer with expiration and interval
	if (clock_gettime(CLOCK_REALTIME, &now) == -1)
		spdlog::get("ll-mec")->error("[RIB UPDATER] clock_gettime");

	its.it_value.tv_sec = now.tv_sec;
	its.it_value.tv_nsec = now.tv_nsec + m_its.it_value.tv_nsec;
	its.it_interval.tv_sec = m_its.it_value.tv_sec;
	its.it_interval.tv_nsec = m_its.it_value.tv_nsec;


	fd = timerfd_create( CLOCK_REALTIME , 0);
	if (fd == -1)
		spdlog::get("ll-mec")->error("[RIB UPDATER] timerfd_create");

	if (timerfd_settime(fd, TFD_TIMER_ABSTIME, &its, NULL) == -1)
		spdlog::get("ll-mec")->error("[RIB UPDATER] timerfd_settime");

	spdlog::get("ll-mec")->debug("[RIB UPDATER] timer started");

	while(1) // keep checking
	{
		s = read(fd, &exp, sizeof(uint64_t));
		if (s != sizeof(uint64_t))
			spdlog::get("ll-mec")->error("[RIB UPDATER] read");
		update_rib();
	}

}


void rib_updater::update_rib()
{
	spdlog::get("ll-mec")->info("[RIB UPDATER] update rib");
	json jsonData;
	//if flexran mode -> update RIB from FlexRAN Controller
	if (m_mode.compare("flexran") == 0){
		spdlog::get("ll-mec")->debug("[RIB UPDATER] Update RIB from FlexRAN controllers");
		//for the moment, get data from only one FlexRAN controller
		for (auto i = m_flexRANControllers.begin(); i != m_flexRANControllers.end(); i++){
			jsonData  = getRANStatistics((i)->first, (i)->second);
			//if (!jsonData.empty()) break;
		}
	} else { //get info from a default json file
		spdlog::get("ll-mec")->debug("[RIB UPDATER] Update RIB from a default Json file");
		jsonData =  getRANStatistics(DEFAULT_RIB_FILE);
	}

	if (!jsonData.empty()){

		json eNB_config, eNB, cellConfig, UE, ueConfig;
		std::string imsi;
		uint64_t eNBId;
		try{
			eNB_config =  json (jsonData["eNB_config"]);
			eNB =  (eNB_config.at(0))["eNB"];
			eNBId = std::stoull(eNB["eNBId"].get<std::string>().c_str());
			cellConfig = eNB["cellConfig"];
			UE = (eNB_config.at(0))["UE"];
			ueConfig = UE["ueConfig"];
			imsi = ((ueConfig.at(0))["imsi"]).get<std::string>().c_str();
		} catch (json::exception& e){
			std::cout << "message: " << e.what() << '\n'
					<< "exception id: " << e.id << std::endl;
		}
		//update DB
		m_rib.update_ue_info(imsi, ueConfig);
		m_rib.update_eNB_info(eNBId, cellConfig);
	}
}

json rib_updater::getRANStatistics(std::string addr, int port)
{
	json jsonData;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charsets: utf-8");

	CURL *curl = curl_easy_init();
	std::string url = addr + ":" + std::to_string(port) + "/stats";
	spdlog::get("ll-mec")->debug("[RIB UPDATER] FlexRAN URL: {} ", url);

	if(curl) {
		CURLcode res;

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		//curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:9999/stats" );
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str() );
		curl_easy_setopt(curl, CURLOPT_HTTPGET,1);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, FLEXRAN_CURL_TIMEOUT_MS);

		// Response information.
		long httpCode(0);
		std::unique_ptr<std::string> httpData(new std::string());

		// Hook up data handling function.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
		res = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		spdlog::get("ll-mec")->debug("[RIB UPDATER] Response from FlexRAN, HTTP code: {} ", httpCode);
		curl_easy_cleanup(curl);

		if (httpCode == 200)
		{
			spdlog::get("ll-mec")->debug("[RIB UPDATER] Got successful response from FlexRAN, URL: {} ", url);
			spdlog::get("ll-mec")->debug("[RIB UPDATER] RAN statistics from FlexRAN: {} ", *httpData.get());
			try{
				jsonData = json::parse(*httpData.get() );
			} catch (json::exception& e){
				spdlog::get("ll-mec")->warn("[RIB UPDATER] Couldn't Parse json data from FlexRAN, URL: {} ", url);
				return json();
			}
			return jsonData;
		}
		else
		{
			spdlog::get("ll-mec")->debug("[RIB UPDATER] Couldn't GET response from FlexRAN, URL: {} ", url);
			return json(); //return an empty json
		}
	}

	return json(); //return an empty json

}

json rib_updater::getRANStatistics(std::string path)
{
	//load Json data from Json file to a json object
	std::ifstream in(path);
	//error when loading data.
	if(!in.is_open())
	{
		return nullptr;
	}
	json jsonData = json::parse(in);
	in.close();
	spdlog::get("ll-mec")->debug("[RIB UPDATER] Imported json data from a file:\n {} ", jsonData.dump());
	return jsonData;
}

/*
 * To read content of the response from FlexRAN controller
 */
static std::size_t callback(
		const char* in,
		std::size_t size,
		std::size_t num,
		std::string* out)
{
	const std::size_t totalBytes(size * num);
	out->append(in, totalBytes);
	return totalBytes;
}
}
}
}
