#ifndef __CONF_H__
#define __CONF_H__

#include "json.h"

using json = nlohmann::json;

class Conf
{
  public:
    /* Static access method. */
    static Conf* getInstance();
    void parse_config();
    std::string config_path;
    json X;
  private:
    /* Here will be the instance stored. */
    static Conf* instance;

    /* Private constructor to prevent instancing. */
    Conf(){}
};

#endif
