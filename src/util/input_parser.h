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

