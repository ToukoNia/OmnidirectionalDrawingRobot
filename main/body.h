//body.h
#ifndef body_h
#define body_h
#include "OmnidirectionalController.h"
#include <Arduino.h>
#include <NewPing.h>
#define DISTANCE_BUFFER 2
#define K 0.4

class RobotBody { 
  private:
    NewPing Ultrasonics[2]={NewPing(25,27),NewPing(29,31)};  //0 is in line with x axis, 1 is in line with the y axis on the robot
    OmnidirectionalController base;
    int distance; int lengths[2]; int error;
  public:
    void StartSequence();
    void FinalStretch();
    void Setup();
    void findDistance(bool direction);
    void staticDistance(int targetDistance, bool sideDirection, int robotDirection);
    void findWall(int targetDistance, int staticDistance, bool forwardDirection, bool sideDirection, bool robotOrientation);
};
#endif