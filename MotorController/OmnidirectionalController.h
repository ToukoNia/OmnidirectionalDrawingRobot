// MotorController.h
#ifndef OmnidirectionalController_h
#define OmnidirectionalController_h

#define wheelDistance 9.36  //distance from the base in cm
#define wheelRadius 3.9139 //radius of the wheel in cm

#include <Arduino.h>
#include "MotorController.h"
class OmnidirectionalController {
  private:
    MotorController Motors[3];
    const float sineVal[3]={0,0.866025,-0.866025};
    const float cosVal[3]={1,-0.5,-0.5};
    float motorVector=0;
    unsigned int sysSpeed;
  public:
    void setupPins(unsigned int sysSpeed);
    void calculateTrajectory(int x, int y, int w);
    void staticDistance(int targetDistance);
};
#endif