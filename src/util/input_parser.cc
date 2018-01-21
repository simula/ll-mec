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

#include <algorithm>

#include "input_parser.h"

const std::string Input_parser::get_cmd_option(const std::string &option) const
{
  std::vector<std::string>::const_iterator itr;
  itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
  if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
    return *itr;
  }
  static const std::string empty_string("");
  return empty_string;
}

bool Input_parser::cmd_option_exists(const std::string &option) const
{
  return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}

void Input_parser::print_help() {
  /*
  spdlog::get("console")->info("Texture atlas generator for Rightware");
  spdlog::get("console")->info("-h");
  spdlog::get("console")->info("");
  spdlog::get("console")->info("\tThis help");
  spdlog::get("console")->info("");
  spdlog::get("console")->info("-p [PATH]");
  spdlog::get("console")->info("");
  spdlog::get("console")->info("\tRead all the images from [PATH] and generate the result0.jpg and result0.png ");
  spdlog::get("console")->info("\tat the same folder where you run texture-atlas. More results(result1, result2");
  spdlog::get("console")->info("\t, etc) will be generated if necessary");
  */
}
