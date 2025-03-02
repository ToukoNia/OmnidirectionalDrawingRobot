// ColourSensor.h
#ifndef ColourSensor_h
#define ColourSensor_h
#define BLACK 255
#include <Arduino.h>

class ColourSensorArray { //NOTE FOR LATER: this might need bottom and top swapped depending on if we want to rotate and how we handle the black line
  private:
    byte colourSensorPins[6]={0,1,2,3,4,5}; //refer to diagram for physical locations, but goes top, top-left, top-right, bottom-left, bottom-right, bottom. this makes later algos favour forwards and to the left (what we have to do)
     byte sensors[2];
    int i; bool j; float temp; bool lastXDirection=1; bool xChanged=0;
    float sensorXDistance[6]={0,-1.4142,1.4142,-1.4142,1.4142,0}; //holds the precalced coords for x and y values
    float sensorYDistance[6]={2.4142,1,1,-1,-1,-2.4142};
    void normalise();
  public:
    void detectLine();
    int x; int y;
    int readSensors(int colour);
    void assignAngle();
    void reverseVector();
    void getCoordinates(float *xN,float *yN);
};
#endif