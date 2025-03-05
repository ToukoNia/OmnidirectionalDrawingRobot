//body.h
#ifndef body_h
#define body_h
#include "OmnidirectionalController.h"
#include <Arduino.h>


class RobotBody { 
  private:
    OmnidirectionalController base;
    float x; float y;
  public:
    void StartSequence();
    void Setup();
    void FirstTunnel();
};
#endif