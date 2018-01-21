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

#include <iostream>
#include "basic_switch.h"
#include "spdlog.h"

namespace llmec {
namespace app {
namespace basic_switch {

void Basic_switch::event_callback(llmec::core::eps::ControllerEvent* ev) {
  if (ev->get_type() == llmec::core::eps::EVENT_SWITCH_UP) {
    this->of_interface.install_default_flow(ev->of_conn_);
    spdlog::get("ll-mec")->info("Switch id={} installed default flow", ev->of_conn_->get_id());
    switch_set_.insert(ev->of_conn_->get_id());
  }
}
std::unordered_set<int> Basic_switch::get_switch_list() {
  return this->switch_set_;
}
void Basic_switch::start() {
  while(true){
    //std::cout<<"Switch"<<std::endl;
  }
}

} // namespace basic_switch
} // namespace app
} // namespace llmec
