/* The MIT License (MIT)

   Copyright (c) 2018 Anta Huang (anta.huang@eurecom.fr)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
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
};

} // namespace data
} // namespace llmec
#endif
