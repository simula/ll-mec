/*
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
  \file
  \brief
  \author
  \company
  \email:
*/

#ifndef __CONTEXT_MANAGER_H__
#define __CONTEXT_MANAGER_H__

#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <utility>

#include "json.h"

using json = nlohmann::json;

namespace llmec {
namespace data {

class Context_manager {
  public:
    static void create_instance();
    static Context_manager* get_instance();

    /* Store the bearer into database */
    bool add_bearer(json context);

    /* Store the bearer with the indicated id into database */
    bool add_bearer(uint64_t id, json context);

    /* Remove the bearer information from database */
    bool delete_bearer(uint64_t id);

    /* Add redirect information into one existing bearer */
    bool add_redirect_bearer(uint64_t id, json context);

    /* Remove redirect information from one existing bearer */
    bool delete_redirect_bearer(uint64_t id);

    /* Add the switch connection id */
    bool add_switch(int switch_id);

    /* Remove the switch connection id */
    bool delete_switch(int switch_id);

    /* Return the number of connected switches */
    int nums_switch();

    /* Clean all tables */
    bool clean();

    /* ID related */
    std::vector<uint64_t> get_id_list();
    std::vector<uint64_t> get_slice_id_list();
    bool id_exist(uint64_t id);

    /* Get the value by key for those 3 tables */
    json get_bearer_context(uint64_t id);
    uint64_t get_id(std::string imsi, uint64_t eps_bearer_id);
    json get_slice_group(uint64_t slice_id);
    std::unordered_set<int> get_switch_set();

    /* Useful function to dump the tables */
    void imsi_mapping_dump();
    void bearer_context_dump();
    void slice_group_dump();

  private:
    std::unordered_set<uint64_t> bag_of_occupied_ids;
    std::mutex context_lock;
    std::mutex id_lock;
    static Context_manager* instance;
    uint64_t next_id();
    Context_manager() {}
    bool sanitize(json bearer_context);

    /* id <-> bearer info in json, the unit */
    std::unordered_map<uint64_t, json> bearer_context;

    /* pair<imsi, bearer_id> <-> id */
    std::map<std::pair<std::string, uint64_t>, uint64_t> imsi_mapping;

    /* slice_id <-> set<id> */
    std::map<uint64_t, std::set<uint64_t>> slice_group;

    /* set of switches connected to this ll-mec controller */
    std::unordered_set<int> switch_set;

};

} // namespace data
} // namespace llmec
#endif
