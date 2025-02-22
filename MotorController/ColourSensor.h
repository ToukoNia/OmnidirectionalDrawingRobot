// ColourSensor.h
#ifndef ColourSensor_h
#define ColourSensor_h
#include <Arduino.h>

class ColourSensorArray { //NOTE FOR LATER: this might need bottom and top swapped depending on if we want to rotate and how we handle the black line
  private:
    byte colourSensorPins[6]={0,1,2,3,4,5}; //refer to diagram for physical locations, but goes top, top-left, top-right, bottom-left, bottom-right, bottom. this makes later algos favour forwards and to the left (what we have to do)
    int x; int y; byte sensors[2];
    int i; bool j; float temp; bool lastXDirection=1; bool lastYDirection=1;
    float sensorXDistance[6]={0,-1.4142,1.4142,-1.4142,1.4142,0}; //holds the precalced coords for x and y values
    float sensorYDistance[6]={2.4142,1,1,-1,-1,-2.4142};
    void normalise();
  public:
    void readSensors(int colour);
    void assignAngle();
};
#endif