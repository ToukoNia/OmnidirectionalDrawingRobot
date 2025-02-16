#include "OmnidirectionalController.h"
OmnidirectionalController base;
void setup(){
  base.setupPins(50);
  Serial.begin(9600);
}

void loop(){
  delay(3000);
  base.calculateTrajectory(1, 0, 0);
  delay(5000);
  base.calculateTrajectory(0, 1, 0);
  delay(5000);
  base.calculateTrajectory(0,0,1);
  delay(3000);
  base.calculateTrajectory(0.66,0.66, 0);
  delay(4000);
  base.calculateTrajectory(0, 0,0);
}