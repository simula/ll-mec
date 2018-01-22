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

#include "ue_manager.h"
#include "spdlog.h"
#include <iostream>

namespace llmec {
namespace app {
namespace uplane {

void Ue_manager::event_callback(llmec::core::eps::ControllerEvent* ev) {
}
void Ue_manager::start() {
/*  while(true){
  }*/
}
bool Ue_manager::add_ue(uint64_t ue_id, std::string imsi, uint64_t s1_ul_teid, uint64_t s1_dl_teid, std::string ue_ip, std::string enb_ip) {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);

  /* Return if connection does not exist */
  if (of_conn_ == nullptr || !of_conn_->is_alive())
    return false;
  this->of_interface.install_default_UE_ul_flow(of_conn_, ue_id, s1_ul_teid);
  this->of_interface.install_default_UE_dl_flow(of_conn_, ue_id, ue_ip, s1_dl_teid, enb_ip);

  /* Store the ue context into thread safe map */
  this->ue_context_lock.lock();
  json ue_context_json;
  ue_context_json["ue_id"] = ue_id;
  ue_context_json["imsi"] = imsi;
  ue_context_json["ue_ip"] = ue_ip;
  ue_context_json["enb_ip"] = enb_ip;
  ue_context_json["s1_ul_teid"] = s1_ul_teid;
  ue_context_json["s1_dl_teid"] = s1_dl_teid;
  this->ue_context[ue_id] = ue_context_json;
  this->ue_context_lock.unlock();

  spdlog::get("ll-mec")->info("Add UE: {}", ue_context_json.dump());
  return true;
}
bool Ue_manager::redirect_ue(uint64_t ue_id, uint64_t s1_ul_teid, uint64_t s1_dl_teid, std::string ue_ip, std::string enb_ip, std::string from, std::string to) {
  /* No such ue context */
  if (this->ue_context.find(ue_id) == this->ue_context.end())
    return false;

  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);

  /* Return if connection does not exist */
  if (of_conn_ == nullptr || !of_conn_->is_alive())
    return false;
  this->of_interface.redirect_edge_service_ul_flow(of_conn_, ue_id, s1_ul_teid, from, to);
  this->of_interface.redirect_edge_service_dl_flow(of_conn_, ue_id, ue_ip, s1_dl_teid, enb_ip, from, to);

  /* Add redirect information in ue context */
  this->ue_context_lock.lock();
  json redirect;
  redirect["from"] = from;
  redirect["to"] = to;
  (this->ue_context[ue_id])["redirect"] = redirect;
  this->ue_context_lock.unlock();

  spdlog::get("ll-mec")->info("Redirected UE id={} from {} to {}", ue_id, from, to);
  return true;
}

bool Ue_manager::delete_redirect_ue(uint64_t ue_id) {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);

  /* Return if connection does not exist */
  if (of_conn_ == nullptr || !of_conn_->is_alive())
    return false;
  /* No such ue context */
  if (this->ue_context.find(ue_id) == this->ue_context.end())
    return false;

  json ue = this->ue_context[ue_id];
  this->of_interface.flush_flow(of_conn_, ue_id);
  this->of_interface.install_default_UE_ul_flow(of_conn_, ue_id, ue["s1_ul_teid"].get<int>());
  this->of_interface.install_default_UE_dl_flow(of_conn_, ue_id, ue["ue_ip"].get<std::string>(), ue["s1_dl_teid"].get<int>(), ue["enb_ip"].get<std::string>());

  /* Remove redirect information in UE context */
  this->ue_context_lock.lock();
  this->ue_context.at(ue_id).erase("redirect");
  this->ue_context_lock.unlock();

  spdlog::get("ll-mec")->info("No redirected traffic for UE id={}", ue_id);
  return true;
}

json Ue_manager::get_ue(uint64_t ue_id) {
  json response = json::array();
  this->ue_context_lock.lock();
  if (this->ue_context.find(ue_id) != this->ue_context.end())
    response.push_back(this->ue_context[ue_id]);
  this->ue_context_lock.unlock();
  return response;
}

json Ue_manager::get_ue_all() {
  json response = json::array();
  this->ue_context_lock.lock();
  for (auto each:this->ue_context)
    if (each.second != nullptr)
      response.push_back(each.second);
  this->ue_context_lock.unlock();
  return response;
}

bool Ue_manager::delete_ue(uint64_t ue_id) {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);

  /* Return if connection does not exist */
  if (of_conn_ == nullptr || !of_conn_->is_alive())
    return false;
  this->of_interface.flush_flow(of_conn_, ue_id);

  /* Remove the ue context */
  this->ue_context_lock.lock();
  this->ue_context.erase(ue_id);
  this->ue_context_lock.unlock();

  spdlog::get("ll-mec")->info("Removed UE id={}", ue_id);
  return true;
}

bool Ue_manager::delete_ue_all() {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);

  /* Return if connection does not exist */
  if (of_conn_ == nullptr || !of_conn_->is_alive())
    return false;
  /* flush flow for each ue and clear the map */
  this->ue_context_lock.lock();
  for (auto each:this->ue_context) {
    this->of_interface.flush_flow(of_conn_, each.first);
  }
  this->ue_context.clear();
  this->ue_context_lock.unlock();

  spdlog::get("ll-mec")->info("Removed all UEs");
  return true;
}

std::vector<uint64_t> Ue_manager::get_ue_list() {
  std::vector<uint64_t> keys;
  this->ue_context_lock.lock();
  keys.reserve(this->ue_context.size());
  for(auto kv : this->ue_context)
    keys.push_back(kv.first);
  this->ue_context_lock.unlock();
  return keys;
}

Ue_manager* Ue_manager::instance = 0;

void Ue_manager::create_instance(llmec::core::eps::OFInterface &of_interface)
  {
    if (instance == 0) {
      instance = new Ue_manager(of_interface);
    }
  }

Ue_manager* Ue_manager::get_instance()
{
  assert(instance);
  return instance;
}


} // namespace uplane
} // namespace app
} // namespace llmec
