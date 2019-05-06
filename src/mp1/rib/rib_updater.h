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
#ifndef RIB_UPDATER_H_
#define RIB_UPDATER_H_

using json = nlohmann::json;

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
	rib_updater (Rib& rib,struct itimerspec its,std::vector<std::pair<std::string, int>> flexRANControllers,std::string mode):
		m_rib(rib), m_its(its), m_flexRANControllers (flexRANControllers), m_mode(mode){
    }
	void run();
	void update_rib();

    /*
     * Get RAN statistics from a FlexRAN controller
     * @param [str] FlexRAN Controller's address
     * @param [port] FlexRAN's port
     * @return RAN statistics
     */
    json getRANStatistics(std::string addr, int port);

    /*
     * Get Json data from a default Json file
     * @param [str] Path to the default Json file
     * @return RAN statistics
     */
    json getRANStatistics(std::string path);
private:
     Rib& m_rib;
     struct itimerspec m_its;
     std::vector<std::pair<std::string, int>> m_flexRANControllers;
     std::string m_mode;


};

}
}
}

#endif
