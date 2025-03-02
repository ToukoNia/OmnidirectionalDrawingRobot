// MotorController.h
#ifndef OmnidirectionalController_h
#define OmnidirectionalController_h
#define encPinA 2
#define EncoderVal 6.7


#include <Arduino.h>
#include "MotorController.h"
#include "ultrasonic.h"
class OmnidirectionalController {
  private:
    MotorController Motors[3];
    Ultrasonic Ultrasonics[2];  //0 is in line with y axis, 1 is in line with the x axis on the robot
    const float sineVal[3]={0,0.866025,-0.866025};
    const float cosVal[3]={1,-0.5,-0.5};
    float motorVector;
    unsigned int sysSpeed;
    int encCount;
    int value;
    int i=0;
    
  public:
    void setupPins(unsigned int systemSpeed);
    void calculateTrajectory(float x, float y);
    void staticDistance(int targetDistance, bool sideDirection);
    void findWall(int targetDistance, int staticDistance, bool forwardDirection, bool sideDirection);
    void Rotate(int w);
};
#endif