//ColourSensorArray.cpp
#include "ColourSensor.h"

void ColourSensorArray::detectLine(){
  while (1){
    if (analogRead(colourSensorPins[0])==BLACK){
      return;
    }
  }
}

int ColourSensorArray::readSensors(int colour){
  for (i=0;i<6;i++){  //loops through, reads from the sensors and assigns any lit pins to an array for later.
      if (analogRead(colourSensorPins[i])>=colour){ 
        if (!j){
          sensors[0]=i;
          j=1;
        } else{
          sensors[1]=i;
          j=0;
          return 1;
        }
      }
  }
  j=0;
  return 0;
} //plan to extend this for case off the line: add flag j=2 for 2 found. if j!=2, then we return 1 from function (otherwise 0). Make new function that does the opposite of the main function to cawlculate opposite vector.

void ColourSensorArray::assignAngle(){  
  x=sensorXDistance[sensors[0]]-sensorXDistance[sensors[1]];  //naturally calculates left and up being positive due to which pins are connected
  y=sensorYDistance[sensors[0]]-sensorYDistance[sensors[1]];  //"

  if (!x && (sensors[0]==1||sensors[0]==2)){
    x=(sensors[0]==1) ? 0.5 : -0.5;
  }
  if (lastXDirection!=(x>=0)&&!xChanged){ //gonna ternary this later but thought id leave it like this so the logic is easier for others to understand
    y=-y;
    x=-x;
  }
  lastXDirection=(x>=0);
  xChanged=!x; 
}

void ColourSensorArray::normalise(){  //normalises the vector so the system total speed nvr goes over the system speed
  temp=sqrt(sq(x)+sq(y));
  x=x/i;
  y=y/i;
}

void ColourSensorArray::reverseVector(){
  x=-x;
  y=-y;
}

void ColourSensorArray::getCoordinates(float *xN, float *yN){
  *xN=x;
  *yN=y;
}