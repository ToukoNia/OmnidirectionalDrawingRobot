#include "body.h"
#include "Arm.h"
RobotBody body;
Arm RobotArm;
void setup(){
  Serial.begin(9600);
  RobotArm.Setup();
  body.Setup();
}

void loop(){
  delay(100);
  body.StartSequence();
  RobotArm.drawLine();
  delay(100);
  body.FinalStretch();
  delay(500);
  RobotArm.dropPen();
  delay(5000);
}