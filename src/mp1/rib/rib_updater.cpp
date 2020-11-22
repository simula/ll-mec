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
#define FLEXRAN_NUMBER_RETRIES 3
#define MAX_WAIT_MSECS 1000 //1second
#define DEFAULT_FLEXRAN_PORT  9999
#define DEFAULT_FLEXRAN_ADDR  "127.0.0.1"
#define HTTP_STATUS_OK 200
namespace llmec {
namespace mp1 {
namespace rib {

typedef struct curl_multi_interface {
  CURL *easy;
  nlohmann::json *jsonData;
}curl_multi_interface_t;

rib_updater::rib_updater (Rib& rib, llmec::event::subscription& ev, struct itimerspec its,std::vector<std::pair<std::string, int>> flexRANControllers,std::string mode):
	m_rib(rib), m_event_sub(ev), m_its(its), m_flexRANControllers (flexRANControllers), m_mode(mode){
	  curl_global_init(CURL_GLOBAL_ALL);
	  m_curl_multi = curl_multi_init();
}

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
		//in case of an easy-single curl request
		//update_rib();

		//for curl multi interface
		if (m_mode.compare("flexran") != 0){
			get_RAN_statistic_from_default_file();
		} else {
			//put flexRAN info into the map
			for (auto i = m_flexRANControllers.begin(); i != m_flexRANControllers.end(); i++){
				m_flexRANStatistics.insert(make_pair(make_pair((i)->first,(i)->second),std::string()));
			}
			send_curl_multi();
			process_curl_multi();
			//process statistics data and store in to a DB
			for (auto i = m_flexRANControllers.begin(); i != m_flexRANControllers.end(); i++){
				get_RAN_statistics_from_FlexRAN((i)->first,(i)->second);
			}
		}
	}
}

bool rib_updater::get_RAN_statistic_from_default_file(){

  nlohmann::json jsonData;
	//load Json data from Json file to a json object
	std::ifstream in(DEFAULT_RIB_FILE);
	//error when loading data.
	if(!in.is_open())
	{
    return false;
	}
	jsonData = nlohmann::json::parse(in);
	in.close();
	spdlog::get("ll-mec")->debug("[RIB UPDATER] Imported json data from the default file:\n {} ", jsonData.dump());

	//if success, try to update the DB
	if (!jsonData.empty()){
	  nlohmann::json eNB_config, eNB, cellConfig, UE, ueConfig;
		std::string imsi;
		uint64_t eNBId;
		try{
			eNB_config =  nlohmann::json (jsonData["eNB_config"]);
			eNB =  (eNB_config.at(0))["eNB"];
			eNBId = std::stoull(eNB["eNBId"].get<std::string>().c_str());
			cellConfig = eNB["cellConfig"];
			UE = (eNB_config.at(0))["UE"];
			ueConfig = UE["ueConfig"];
			//imsi = ((ueConfig.at(0))["imsi"]).get<std::string>().c_str();
			int numUEConfig = ueConfig.size();
			for (int i = 0; i < numUEConfig; i++){
				imsi = ((ueConfig.at(i))["imsi"]).get<std::string>().c_str();
				//should add timestamp to the DB
				//update DB
			    m_rib.update_ue_info(imsi, ueConfig.at(i));
			}
			m_rib.update_eNB_info(eNBId, cellConfig);

		} catch (nlohmann::json::exception& e){
			std::cout << "message: " << e.what() << '\n'
					<< "exception id: " << e.id << std::endl;

			//TODO: should we reset the corresponding field in the DB?
			return false;
		}

		//update DB
		//m_rib.update_ue_info(imsi, ueConfig);
		//m_rib.update_eNB_info(eNBId, cellConfig);
	}
	else{
		spdlog::get("ll-mec")->warn("[RIB UPDATER] No valid data from the default file {} ",DEFAULT_RIB_FILE);
	}

	return true;

}
void rib_updater::update_rib()
{
	spdlog::get("ll-mec")->info("[RIB UPDATER] update rib");
	nlohmann::json jsonData;
	//if flexran mode -> update RIB from FlexRAN Controller
	if (m_mode.compare("flexran") == 0){
		spdlog::get("ll-mec")->debug("[RIB UPDATER] Update RIB from FlexRAN controllers");

		//for the moment, get data from only one FlexRAN controller
		for (auto i = m_flexRANControllers.begin(); i != m_flexRANControllers.end(); i++){
			jsonData  = getRANStatistics((i)->first, (i)->second);
			if (!jsonData.empty()) break;
		}
	} else { //get info from a default json file
		spdlog::get("ll-mec")->debug("[RIB UPDATER] Update RIB from a default Json file");
		jsonData =  getRANStatistics(DEFAULT_RIB_FILE);
	}

	if (!jsonData.empty()){

	  nlohmann::json eNB_config, eNB, cellConfig, UE, ueConfig;
		std::string imsi;
		uint64_t eNBId;
		try{
			eNB_config =  nlohmann::json (jsonData["eNB_config"]);
			eNB =  (eNB_config.at(0))["eNB"];
			eNBId = std::stoull(eNB["eNBId"].get<std::string>().c_str());
			cellConfig = eNB["cellConfig"];
			UE = (eNB_config.at(0))["UE"];
			ueConfig = UE["ueConfig"];
			int numUEConfig = ueConfig.size();

			for (int i = 0; i < numUEConfig; i++){
				imsi = ((ueConfig.at(i))["imsi"]).get<std::string>().c_str();
				//should add timestamp to the DB
				//update DB
			    m_rib.update_ue_info(imsi, ueConfig.at(i));
			}
			m_rib.update_eNB_info(eNBId, cellConfig);

		} catch (nlohmann::json::exception& e){
			std::cout << "message: " << e.what() << '\n'
					<< "exception id: " << e.id << std::endl;
		}

	}

}


//TODO: make in run in parallel as in flexran Elastic search
nlohmann::json rib_updater::getRANStatistics(std::string addr, int port)
{
  nlohmann::json jsonData;
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
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData);
		bool isFlexRANReady = false;
		int numRetries = 0;
		while (numRetries < FLEXRAN_NUMBER_RETRIES){
			res = curl_easy_perform(curl);
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
			spdlog::get("ll-mec")->debug("[RIB UPDATER] Response from FlexRAN, HTTP code: {} ", httpCode);

			if (httpCode == HTTP_STATUS_OK)
			{
				spdlog::get("ll-mec")->debug("[RIB UPDATER] Got successful response from FlexRAN, URL: {} ", url);
				spdlog::get("ll-mec")->debug("[RIB UPDATER] RAN statistics from FlexRAN: {} ", *httpData.get());
				try{
					jsonData = nlohmann::json::parse(*httpData.get());
					curl_easy_cleanup(curl);
					return jsonData;
				} catch (nlohmann::json::exception& e){
					spdlog::get("ll-mec")->warn("[RIB UPDATER] Couldn't Parse json data from FlexRAN, URL: {} ", url);
				}
				numRetries++;
			}
			else
			{
				spdlog::get("ll-mec")->debug("[RIB UPDATER] Couldn't GET response from FlexRAN, URL: {}, retry ... ", url);
				//retry
				numRetries++;
			}
		}
		curl_easy_cleanup(curl);
		return nlohmann::json(); //return an empty json
	}

	return nlohmann::json(); //return an empty json
}

nlohmann::json rib_updater::getRANStatistics(std::string path)
{
	//load Json data from Json file to a json object
	std::ifstream in(path);
	//error when loading data.
	if(!in.is_open())
	{
		return nullptr;
	}
	nlohmann::json jsonData = nlohmann::json::parse(in);
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

std::string rib_updater::get_flexRAN_IPAddress(std::string str){
	size_t startPos = str.find("\//");
	size_t splitPos = str.find_last_of(":");
	//can not find IP address
	if ((startPos == std::string::npos)| (splitPos == std::string::npos))
		return DEFAULT_FLEXRAN_ADDR;

	std::string addr = str.substr(startPos + 2, splitPos - (startPos + 2));
	return addr;

}

int rib_updater::get_flexRAN_port(std::string str){
	size_t splitPos = str.find_last_of(":");
	size_t endPos = str.find_last_of("/");
	int port;
	//can not find port
	if ((splitPos == std::string::npos)| (endPos == std::string::npos))
		return DEFAULT_FLEXRAN_PORT;

	try {
		port = std::stoi(str.substr(splitPos + 1, endPos - (splitPos + 1)));
	}catch (std::exception const & e){
		return DEFAULT_FLEXRAN_PORT;
	}
	return port;
}

void rib_updater::send_curl_multi()
{
	int still_running = 0;
	int numfds = 0, res = 0, msgs_left = 0;
	CURLMsg *msg = NULL;
	CURL *curl=NULL;
	CURLcode return_code;
	int http_status_code;

	//create and add an easy handle to a  multi curl request
	for (auto i = m_flexRANControllers.begin(); i != m_flexRANControllers.end(); i++){
		std::map<std::pair<std::string, int>, std::string>::iterator it;
		it = m_flexRANStatistics.find(make_pair((i)->first, (i)->second));
		CURL *temp = curl_create_handle((i)->first, (i)->second, &((it)->second) );
		curl_multi_add_handle(m_curl_multi, temp);
	}

	curl_multi_perform(m_curl_multi, &still_running);
	//block until activity is detected on at least one of the handles or MAX_WAIT_MSECS has passed.
	do {
		res = curl_multi_wait(m_curl_multi, NULL, 0, MAX_WAIT_MSECS, &numfds);
		if(res != CURLM_OK) {
			spdlog::get("ll-mec")->error("[RIB UPDATER] error: curl_multi_wait() returned {}!", res);
		}
		curl_multi_perform(m_curl_multi, &still_running);
	} while(still_running);
}


void rib_updater::process_curl_multi()
{
	int res = 0, msgs_left = 0;
	CURLMsg *msg = NULL;
	CURL *curl = NULL;
	CURLcode return_code;
	int http_status_code = 0;
	char *url = NULL;
	std::map<std::pair<std::string, int>, std::string>::iterator it;

	//read the messages
	while ((msg = curl_multi_info_read(m_curl_multi, &msgs_left))) {
		if (msg->msg == CURLMSG_DONE) {
			curl = msg->easy_handle;
			return_code = msg->data.result;
			res = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
			//get address and port of the flexRAN controller, and then find the corresponding controller in the map
			if(url != NULL){
				std::string url_str = url;
				std::string addr = get_flexRAN_IPAddress(url_str);
				int port = get_flexRAN_port(url_str);
				spdlog::get("ll-mec")->debug("[RIB UPDATER] process curl from FlexRAN controller, ADDR: {}, port {} ", addr, port);
				it = m_flexRANStatistics.find(std::make_pair(addr, port));
			} else{
				spdlog::get("ll-mec")->debug("[RIB UPDATER] Default FlexRAN controller, ADDR: {}, port {} ", DEFAULT_FLEXRAN_ADDR, DEFAULT_FLEXRAN_PORT);
				it = m_flexRANStatistics.find(std::make_pair(DEFAULT_FLEXRAN_ADDR, DEFAULT_FLEXRAN_PORT));
			}

			if(return_code != CURLE_OK) {
				spdlog::get("ll-mec")->debug("[RIB UPDATER] CURL error code {} ", msg->data.result);
				//remove the outdated data
				//spdlog::get("ll-mec")->debug("[RIB UPDATER] RAN statistics to be removed {} ", ((it)->second));
				it->second = std::string();
				continue;
			}
			// Get HTTP status code
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status_code);
			//curl_easy_getinfo(curl, CURLINFO_PRIVATE, httpData);

			if(http_status_code == HTTP_STATUS_OK) {
				spdlog::get("ll-mec")->debug("[RIB UPDATER] RAN statistics from FlexRAN: {} ", ((it)->second));
			} else {
				spdlog::get("ll-mec")->debug("[RIB UPDATER] Http status code {} ", http_status_code);
				//reset the data
				it->second = std::string();
			}
			//remove this handle from the multi session and end this handle
			curl_multi_remove_handle(m_curl_multi, curl);
			curl_easy_cleanup(curl);
		}
		else {
			spdlog::get("ll-mec")->error("[RIB UPDATER] error after curl_multi_info_read(), CURLMsg {} ",msg->msg);
		}
	}
}


CURL * rib_updater::curl_create_handle (std::string addr, int port, std::string *httpData){
	//create handle for a curl request
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charsets: utf-8");

	CURL *curl = curl_easy_init();

	if (curl){
		std::string url = addr + ":" + std::to_string(port) + "/stats";
		spdlog::get("ll-mec")->debug("[RIB UPDATER] FlexRAN URL: {} ", url);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str() );
		//curl_easy_setopt(curl, CURLOPT_PRIVATE, str);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
		curl_easy_setopt(curl, CURLOPT_HTTPGET,1);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, FLEXRAN_CURL_TIMEOUT_MS);
		// Hook up data handling function.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	}
	return curl;
}


void rib_updater::get_RAN_statistics_from_FlexRAN(std::string addr, int port)
{
  nlohmann::json jsonData;
	std::map<std::pair<std::string, int>, std::string>::iterator it;
	it = m_flexRANStatistics.find(std::make_pair(addr, port));
	//parse RAN statistic to json format
	try{
		jsonData = nlohmann::json::parse((it)->second);
	} catch (nlohmann::json::exception& e){
		spdlog::get("ll-mec")->warn("[RIB UPDATER] Couldn't parse json data from FlexRAN {}:{} ", addr, port);
		//remove the data for the next update cycle
		it->second = std::string();
		return;
	}
	//if success, try to update the DB
	if (!jsonData.empty()){
	  nlohmann::json eNB_config, eNB, cellConfig, UE, ueConfig;
		std::string imsi;
		uint64_t eNBId;
		try{
			eNB_config =  nlohmann::json (jsonData["eNB_config"]);
			eNB =  (eNB_config.at(0))["eNB"];
			eNBId = std::stoull(eNB["eNBId"].get<std::string>().c_str());
			cellConfig = eNB["cellConfig"];
			UE = (eNB_config.at(0))["UE"];
			ueConfig = UE["ueConfig"];
			//imsi = ((ueConfig.at(0))["imsi"]).get<std::string>().c_str();
			int numUEConfig = ueConfig.size();
			for (int i = 0; i < numUEConfig; i++){
				imsi = ((ueConfig.at(i))["imsi"]).get<std::string>().c_str();
				//should add timestamp to the DB
				//update DB
			    m_rib.update_ue_info(imsi, ueConfig.at(i));
			}
			m_rib.update_eNB_info(eNBId, cellConfig);

		} catch (nlohmann::json::exception& e){
			std::cout << "message: " << e.what() << '\n'
					<< "exception id: " << e.id << std::endl;
			//remove the data for the next update cycle
			it->second = std::string();
			//TODO: should we reset the corresponding field in the DB?
			return;
		}

		//update DB
		//m_rib.update_ue_info(imsi, ueConfig);
		//m_rib.update_eNB_info(eNBId, cellConfig);
	}
	else{
		spdlog::get("ll-mec")->warn("[RIB UPDATER] No valid data from FlexRAN {}:{} ", addr, port);
	}
	//remove the data for the next update cycle
	it->second = std::string();

}

}
}
}
