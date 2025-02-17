// MotorController.h
#ifndef OmnidirectionalController_h
#define OmnidirectionalController_h
#define encPinA 2
#define encPinB 3
#include <Arduino.h>
#include "MotorController.h"
class OmnidirectionalController {
  private:
    MotorController Motors[3];
    const float sineVal[3]={0,0.866025,-0.866025};
    const float cosVal[3]={1,-0.5,-0.5};
    float motorVector;
    unsigned int sysSpeed;
    int encCount;
    int target;
  public:
    void setupPins(unsigned int systemSpeed);
    void calculateTrajectory(float x, float y);
    //void staticDistance(int targetDistance);
    void Rotate(int w);
};
#endif