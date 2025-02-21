//ColourSensorArray.cpp
#include "ColourSensor.h"

void ColourSensorArray::readSensors(int colour){
  for (i=0;i<6;i++){  //loops through, reads from the sensors and assigns any lit pins to an array for later.
      if (analogRead(colourSensorPins[i])>=colour){ 
        if (!j){
          sensors[0]=i;
          j=1;
        } else{
          sensors[1]=i;
          break;
        }
      }
  }
  j=0;
}

void ColourSensorArray::assignAngle(){
  x=sensorXDistance[sensors[0]]-sensorXDistance[sensors[1]];  //favours left side
  y=sensorYDistance[sensors[0]]-sensorYDistance[sensors[1]];  //favours forwards
  if (!y&&lastValue%2==1){  //if its purely horizontal, check the last value. if it was on the right side, flip the logic
    x=-x;
  }
  normalise();
  lastValue=sensors[0]; //will always be the first sensor as we know the robot will always be heading forwards
}

void ColourSensorArray::normalise(){
  temp=sqrt(sq(x)+sq(y));
  x=x/i;
  y=y/i;
}