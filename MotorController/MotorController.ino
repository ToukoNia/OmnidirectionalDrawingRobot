#include "body.h"
#include "Arm.h"
RobotBody body;
Arm RobotArm;
void setup(){
  Serial.begin(9600);
  body.Setup();
  Arm.Setup();
}

void loop(){
  RobotArm.storePosition();
  delay(100);
  body.StartSequence();
  //RobotArm.drawLine();
  RobotArm.storePosition();
  delay(100);
  body.FinalStretch();
  RobotArm.dropPen();
  delay(100);
  RobotArm.storePosition();
  delay(10000);
}