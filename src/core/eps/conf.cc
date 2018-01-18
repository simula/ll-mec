#include <iostream>
#include <fstream>

#include "conf.h"

/* Null, because instance will be initialized on demand. */
Conf* Conf::instance = 0;

Conf* Conf::getInstance()
{
  if (instance == 0)
  {
    instance = new Conf();
  }

  return instance;
}

void Conf::parse_config() {
  if (this->config_path.empty())
    return;
  std::ifstream config_file(this->config_path);
  config_file >> this->X;
}

