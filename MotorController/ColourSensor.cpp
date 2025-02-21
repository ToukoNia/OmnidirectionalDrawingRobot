//MotorController.cpp
#include "ColourSensor.h"

void ColourSensorArray::readSensors(int colour){
  for (i=0;i<6;i++){
      if (analogRead(colourSensorPins[i])>=colour){
        if (!j){
          sensors[0]=i;
          j=1;
        } else{
          sensors[1]=i;
        }
      }
  }
  j=0;
}

void ColourSensorArray::assignAngle(){
  x=sensorXDistance[sensors[0]]-sensorXDistance[sensors[1]];
  y=sensorYDistance[sensors[0]]-sensorYDistance[sensors[1]];
  normalise();
}

void ColourSensorArray::normalise(){
  temp=sqrt(sq(x)+sq(y));
  x=x/i;
  y=y/i;
}