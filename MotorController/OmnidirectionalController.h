// MotorController.h
#ifndef OmnidirectionalController_h
#define OmnidirectionalController_h

#include <Arduino.h>
#include "MotorController.h"
class OmnidirectionalController {
  private:
    MotorController Motors[3];
    const float sineVal[3]={0,0.866025,-0.866025};
    const float cosVal[3]={1,-0.5,-0.5};
    float motorVector;
    unsigned int sysSpeed;
  public:
    void setupPins(unsigned int systemSpeed);
    void calculateTrajectory(float x, float y, float w);
    void staticDistance(int targetDistance);
};
#endif