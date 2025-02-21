// MotorController.h
#ifndef ColourSensor_h
#define ColourSensor_h
#include <Arduino.h>

class ColourSensorArray {
  private:
    byte colourSensorPins[6]={0,1,2,3,4,5};
    int x; int y; byte sensors[2];
    int i; bool j; float temp;
    float sensorXDistance[6]={0,-1.4142,1.4142,-1.4142,1.4142,0};
    float sensorYDistance[6]={2.4142,1,1,-1,-1,-2.4142};
    void normalise();
  public:
    void readSensors(int colour);
    void assignAngle();

};
#endif