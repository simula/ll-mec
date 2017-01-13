#include <iostream>
#include "controller.h"
int main(){
  Controller ctrl("0.0.0.0", 6653, 2);

  ctrl.start();
  wait_for_sigint();
  ctrl.stop();
  return 0;
}
