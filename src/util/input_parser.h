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

#ifndef __INPUT_PARSER_H__
#define __INPUT_PARSER_H__
#include <string>
#include <vector>

/*
 * parse the input and possiblly sanitize 
 */

class Input_parser {
  public:
    Input_parser(int &argc, char **argv)
    {
      for (int i=1; i < argc; ++i)
        this->tokens.push_back(std::string(argv[i]));
    }
    const std::string get_cmd_option(const std::string &option) const;
    bool cmd_option_exists(const std::string &option) const;
    static void print_help();
  private:
    std::vector <std::string> tokens;
};

#endif

