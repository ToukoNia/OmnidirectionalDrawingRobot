//body.h
#ifndef body_h
#define body_h
#include "OmnidirectionalController.h"
#include "ColourSensor.h"
#include <Arduino.h>


class RobotBody { 
  private:
    ColourSensorArray lineDetector;
    OmnidirectionalController movement;
    float x; float y;
  public:
    void StartSequence();
    void LineFollowing(int colour);
};
#endif