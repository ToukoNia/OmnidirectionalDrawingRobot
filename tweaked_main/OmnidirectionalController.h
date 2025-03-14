// MotorController.h
#ifndef OmnidirectionalController_h
#define OmnidirectionalController_h
#define encPinA 2
#define EncoderVal 6.7


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
    int value;
    int i=0;
  public:
    void setupPins(unsigned int systemSpeed);
    void calculateTrajectory(float x, float y);
    void Rotate(int w);
    void updateSpeed(unsigned int speed);
    void brk();
};
#endif