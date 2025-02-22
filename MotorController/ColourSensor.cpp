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
} //plan to extend this for case off the line: add flag j=2 for 2 found. if j!=2, then we return 1 from function (otherwise 0). Make new function that does the opposite of the main function to cawlculate opposite vector.

void ColourSensorArray::assignAngle(){  //need to expand to a case where 0 = additional rather than assuming up
  x=sensorXDistance[sensors[0]]-sensorXDistance[sensors[1]];  //naturally calculates left and up being positive due to which pins are connected
  y=sensorYDistance[sensors[0]]-sensorYDistance[sensors[1]];  //"
  if (lastXDirection==(x>=0)&&!lastYDirection==(y>=0)){ //gonna ternary this later but thought id leave it like this so the logic is easier for others to understand
    y=-y;
  } else if (lastYDirection==(y>=0)&&!lastXDirection==(x>=0)){
    x=-x;
  } //basically if it allows only one direction to be changed at a time.

  normalise();
  lastXDirection=(x>=0); //1 equals left favoured, 0 = right favoured
  lastYDirection=(y>=0); //" but up and then down
}

void ColourSensorArray::normalise(){  //normalises the vector so the system total speed nvr goes over the system speed
  temp=sqrt(sq(x)+sq(y));
  x=x/i;
  y=y/i;
}