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
