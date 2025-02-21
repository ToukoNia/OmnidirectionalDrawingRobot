#include "OmnidirectionalController.h"
OmnidirectionalController base;
void setup(){
  base.setupPins(150);
  Serial.begin(9600);
}

void loop(){
  base.calculateTrajectory(0, 0);
  base.Rotate(180);
  base.calculateTrajectory(0, 0);
  delay(5000);
}