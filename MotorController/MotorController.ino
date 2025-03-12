#include "body.h"
#include "Arm.h"
RobotBody body;
Arm MyArm;
void setup(){
  Serial.begin(9600);
  body.Setup();
  MyArm.Setup();
}

void loop(){
  MyArm.storePosition();
  delay(1000);
  body.StartSequence();
  MyArm.drawLine();
  MyArm.storePosition();
  delay(1000);
  body.FinalStretch();
  MyArm.dropPen();
  delay(100);
  MyArm.storePosition();
  delay(10000);
}