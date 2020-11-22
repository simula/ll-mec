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
  \file rib_updater.h
  \brief header file of rib_updater.cpp to perform the update of RIB from FlexRAN controllers
  \author Tien-Thinh NGUYEN
  \company Eurecom
  \email: thinhnt1983@gmail.com
*/

#include <unistd.h>
#include "rib.h"
#include "subscription.h"
#ifndef RIB_UPDATER_H_
#define RIB_UPDATER_H_

//using json = nlohmann::json;

namespace llmec {
namespace mp1 {
namespace rib {

static std::size_t callback(
        const char* in,
        std::size_t size,
        std::size_t num,
        std::string* out);

class rib_updater {
public:
	rib_updater (Rib& rib, llmec::event::subscription& ev, struct itimerspec its,std::vector<std::pair<std::string, int>> flexRANControllers,std::string mode);

	void run();
	void update_rib();

    /*
     * Get RAN statistics from a FlexRAN controller
     * @param [str] FlexRAN Controller's address
     * @param [port] FlexRAN's port
     * @return RAN statistics
     */
	nlohmann::json getRANStatistics(std::string addr, int port);

    /*
     * Get Json data from a default Json file
     * @param [str] Path to the default Json file
     * @return RAN statistics
     */
	nlohmann::json getRANStatistics(std::string path);

    /*
     * Send curl request to FlexRAN controllers in parallel
     * @return void
     */
    void send_curl_multi();

    /*
     * Create an easy single handle for each FlexRAN controller to be added to a multi session
     * @param [addr] Address of the FlexRAN Controller
     * @param [port] Port number of the FlexRAN Controller
     * @param [httpData] Variable to store the return data
     * @return a pointer to the created handle
     */
    CURL * curl_create_handle (std::string addr, int port, std::string *httpData);

    /*
     * Process the multi session request and store the returned data into a DB
     */
    void process_curl_multi();

    /*
     * Get RAN statistics from a FlexRAN controller and store in the DB
     * @param [str] FlexRAN Controller's address
     * @param [port] FlexRAN's port
     * @return void
     */
    void get_RAN_statistics_from_FlexRAN(std::string addr, int port);

    bool get_RAN_statistic_from_default_file();

    /*
     * Get FlexRAN's IP address from its URL
     * @param [url] FlexRAN's URL
     * @return FlexRAN's IP address
     */
    std::string get_flexRAN_IPAddress(std::string url);
    /*
     * Get FlexRAN's port number from its URL
     * @param [url] FlexRAN's URL
     * @return FlexRAN's port number
     */
    int get_flexRAN_port(std::string url);


private:
     Rib& m_rib;
     llmec::event::subscription& m_event_sub;
     struct itimerspec m_its;
     //uint64_t m_duration;
     std::vector<std::pair<std::string, int>> m_flexRANControllers;
	 std::map<std::pair<std::string, int>, std::string> m_flexRANStatistics;
     std::string m_mode;
     CURLM* m_curl_multi;

};

}
}
}

#endif
