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
void Ue_manager::add_ue(uint64_t s1_ul_teid, uint64_t s1_dl_teid, std::string ue_ip, std::string enb_ip) {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);
  this->of_interface.install_default_UE_ul_flow(of_conn_, s1_ul_teid);
  this->of_interface.install_default_UE_dl_flow(of_conn_, ue_ip, s1_dl_teid, enb_ip);
}
void Ue_manager::redirect_ue(uint64_t s1_ul_teid, uint64_t s1_dl_teid, std::string ue_ip, std::string enb_ip, std::string from, std::string to) {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);
  this->of_interface.redirect_edge_service_ul_flow(of_conn_, s1_ul_teid, from, to);
  this->of_interface.redirect_edge_service_dl_flow(of_conn_, ue_ip, s1_dl_teid, enb_ip, from, to);
}
void Ue_manager::flush_flow(uint64_t cookie) {
  llmec::core::eps::Controller* ctrl = llmec::core::eps::Controller::get_instance();
  fluid_base::OFConnection *of_conn_ = ctrl->get_ofconnection(ctrl->conn_id);
  this->of_interface.flush_flow(of_conn_, cookie);
}

} // namespace uplane
} // namespace app
} // namespace llmec
