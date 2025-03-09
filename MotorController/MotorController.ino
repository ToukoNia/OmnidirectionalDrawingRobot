#include "body.h"
RobotBody body;
void setup(){
  Serial.begin(9600);
  body.Setup();
}

void loop(){
  body.StartSequence();
 body.FinalStretch();
  delay(10000);
}