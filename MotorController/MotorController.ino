#include "body.h"
RobotBody body;
void setup(){
  Serial.begin(9600);
}

void loop(){
  body.StartSequence();
}