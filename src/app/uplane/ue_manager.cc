#include "ue_manager.h"
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

  return true;
}

bool Ue_manager::delete_redirect_ue(uint64_t ue_id) {
  /* No such ue context */
  if (this->ue_context.find(ue_id) == this->ue_context.end())
    return false;

  json ue = this->ue_context[ue_id];
  this->delete_ue(ue_id);
  this->add_ue(ue_id, ue["imsi"].get<std::string>(), ue["s1_ul_teid"].get<int>(), ue["s1_dl_teid"].get<int>(), ue["ue_ip"].get<std::string>(), ue["enb_ip"].get<std::string>());

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

  return true;
}

} // namespace uplane
} // namespace app
} // namespace llmec
