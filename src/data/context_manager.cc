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

#include <climits>
#include <string>

#include "context_manager.h"
#include "spdlog.h"


namespace llmec {
namespace data {

bool Context_manager::add_bearer(json context)
{
  if (this->sanitize(context) == false)
    return false;

  this->context_lock.lock();
  uint64_t id = this->next_id();
  if (id == 0) {
    spdlog::get("ll-mec")->error("Running out of IDs.");
    this->context_lock.unlock();
    return false;
  }
  context["id"] = id;
  this->imsi_mapping.insert(std::make_pair(std::make_pair(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>()), id));
  this->bearer_context[id] = context;
  this->slice_group[context["slice_id"].get<int>()].insert(id);
  this->context_lock.unlock();
  return true;
}

bool Context_manager::add_bearer(uint64_t id, json context)
{
  if (this->sanitize(context) == false)
    return false;

  this->context_lock.lock();
  context["id"] = id;
  this->imsi_mapping.insert(std::make_pair(std::make_pair(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>()), id));
  this->bearer_context[id] = context;
  this->slice_group[context["slice_id"].get<int>()].insert(id);
  this->context_lock.unlock();
  return true;
}

bool Context_manager::id_exist(uint64_t id)
{
  bool exist = false;
  this->context_lock.lock();
  exist = (this->bearer_context.find(id) != this->bearer_context.end());
  this->context_lock.unlock();
  return exist;
}

bool Context_manager::sanitize(json bearer_context)
{
  /* Pass all of them for the moment */
  return true;
}

bool Context_manager::delete_bearer(uint64_t id)
{
  this->context_lock.lock();
  if (this->bearer_context.count(id) == 0) {
    this->context_lock.unlock();
    return true;
  }
  json context = this->bearer_context[id];
  this->imsi_mapping.erase(std::make_pair(context["imsi"].get<std::string>(), context["eps_bearer_id"].get<int>()));
  this->slice_group[context["slice_id"].get<int>()].erase(context["id"].get<int>());
  if (slice_group[context["slice_id"].get<int>()].empty()) slice_group.erase(context["slice_id"].get<int>());
  this->bearer_context.erase(id);
  this->bag_of_occupied_ids.erase(id);
  this->context_lock.unlock();
  return true;
}

bool Context_manager::add_redirect_bearer(uint64_t id, json context)
{
  this->context_lock.lock();
  if (this->bearer_context.count(id) == 0) {
    this->context_lock.unlock();
    return true;
  }
  (this->bearer_context[id])["redirect"] = context;
  this->context_lock.unlock();
  return true;
}

bool Context_manager::delete_redirect_bearer(uint64_t id)
{
  this->context_lock.lock();
  if (this->bearer_context.count(id) == 0) {
    this->context_lock.unlock();
    return true;
  }
  (this->bearer_context[id]).erase("redirect");
  this->context_lock.unlock();
  return true;
}

json Context_manager::get_bearer_context(uint64_t id)
{
  json context;
  this->context_lock.lock();
  if (this->bearer_context.count(id) != 0)
    context = this->bearer_context.at(id);
  this->context_lock.unlock();
  return context;
}

bool Context_manager::clean()
{
  this->context_lock.lock();
  this->bearer_context.clear();
  this->imsi_mapping.clear();
  this->slice_group.clear();
  this->context_lock.unlock();
}

std::vector<uint64_t> Context_manager::get_id_list()
{
  std::vector<uint64_t> keys;
  this->context_lock.lock();
  keys.reserve(this->bearer_context.size());
  for(auto kv : this->bearer_context)
    keys.push_back(kv.first);
  this->context_lock.unlock();
  return keys;
}

std::vector<uint64_t> Context_manager::get_slice_id_list()
{
  std::vector<uint64_t> keys;
  this->context_lock.lock();
  keys.reserve(this->slice_group.size());
  for(auto kv : this->slice_group)
    keys.push_back(kv.first);
  this->context_lock.unlock();
  return keys;
}

uint64_t Context_manager::get_id(std::string imsi, uint64_t eps_bearer_id)
{
  uint64_t id = 0;
  this->context_lock.lock();
  if (this->imsi_mapping.count(std::make_pair(imsi, eps_bearer_id)) != 0)
    id = this->imsi_mapping.at(std::make_pair(imsi, eps_bearer_id));
  this->context_lock.unlock();
  return id;
}

json Context_manager::get_slice_group(uint64_t slice_id)
{
  json id_array = json::array();
  this->context_lock.lock();
  if (this->slice_group.count(slice_id) != 0) {
    for (auto each:this->slice_group.at(slice_id)) {
      id_array.push_back(each);
    }
  }
  this->context_lock.unlock();
  return id_array;
}

void Context_manager::imsi_mapping_dump()
{
  spdlog::get("ll-mec")->info("");
  spdlog::get("ll-mec")->info("--- IMSI mapping raw dump ---");
  spdlog::get("ll-mec")->info("{:<15},{:<13} | {:<30}", "IMSI", "EPS bearer ID", "Internal ID");
  this->context_lock.lock();
  for (auto each:this->imsi_mapping) {
    spdlog::get("ll-mec")->info("{:<15},{:<13} | {:<5}", each.first.first, each.first.second, each.second);
  }
  this->context_lock.unlock();
  spdlog::get("ll-mec")->info("");
}

void Context_manager::bearer_context_dump()
{
  spdlog::get("ll-mec")->info("");
  spdlog::get("ll-mec")->info("--- Bearer context raw dump ---");
  spdlog::get("ll-mec")->info("{:<11} | {:<50}", "Internal ID", "Bearer context");
  this->context_lock.lock();
  for (auto each:this->bearer_context) {
    spdlog::get("ll-mec")->info("{:<11} | {:<50}", each.first, each.second.dump());
  }
  this->context_lock.unlock();
  spdlog::get("ll-mec")->info("");
}

void Context_manager::slice_group_dump()
{
  spdlog::get("ll-mec")->info("");
  spdlog::get("ll-mec")->info("--- Slice group raw dump ---");
  spdlog::get("ll-mec")->info("{:<8} | {:<50}", "Slice ID", "Group of internally-used bearer ID");
  this->context_lock.lock();
  for (auto each:this->slice_group) {
    std::string set_of_id = "{ ";
    int c = 0;
    for (auto id:each.second) {
      set_of_id = set_of_id + (c == 0 ? "": ", ") + std::to_string(id);
      c++;
    }
    set_of_id += " }";
    spdlog::get("ll-mec")->info("{:<8} | {:<50}", each.first, set_of_id);
  }
  this->context_lock.unlock();
  spdlog::get("ll-mec")->info("");
}

uint64_t Context_manager::next_id()
{
  this->id_lock.lock();
  for (uint64_t i = 1;i<UINT_MAX;i++) {
    if (std::find(std::begin(this->bag_of_occupied_ids), std::end(this->bag_of_occupied_ids), i) == std::end(this->bag_of_occupied_ids)) {
      this->bag_of_occupied_ids.insert(i);
      this->id_lock.unlock();
      return i;
    }
  }
  this->id_lock.unlock();
  return 0;
}

Context_manager* Context_manager::instance = 0;

void Context_manager::create_instance()
{
  if (instance == 0) {
    instance = new Context_manager();
  }
}

Context_manager* Context_manager::get_instance()
{
  assert(instance);
  return instance;
}

}
}