//body.h
#ifndef body_h
#define body_h
#include "OmnidirectionalController.h"
#include <Arduino.h>
#include "ultrasonic.h"

class RobotBody { 
  private:
    Ultrasonic Ultrasonics[2];  //0 is in line with x axis, 1 is in line with the y axis on the robot
    OmnidirectionalController base;
    int distance;
  public:
    void StartSequence();
    void Setup();
    void staticDistance(int targetDistance, bool sideDirection, int robotDirection);
    void findWall(int targetDistance, int staticDistance, bool forwardDirection, bool sideDirection, bool robotOrientation);
    void FirstTunnel();
};
#endif