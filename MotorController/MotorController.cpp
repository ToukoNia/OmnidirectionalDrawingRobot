//MotorController.cpp
#include "MotorController.h"

void MotorController::setupPins(byte inputPinA1, byte inputpinA2, byte inputPinPWM, byte inputPinStandby) {
	pinAI1 = inputPinA1;
  pinAI2 = inputpinA2;
  pinPWM = inputPinPWM;
  pinStandBy = inputPinStandby;
  pinMode(pinAI1, OUTPUT);
  pinMode(pinAI2, OUTPUT);
  pinMode(pinPWM, OUTPUT);
  pinMode(pinStandBy, OUTPUT);
  
  //Initialize the serial port

  // Drive the standby pin high to enable the output
  standBy = true;
  digitalWrite(pinStandBy, standBy);

  // Set Initial values for AI1 and AI2 control function pins
  AI1 = 0;
  AI2 = 0;

  // set an initial value for the PWM value
  pwmValue = 100;
  analogWrite(pinPWM,pwmValue);
}

//breaks for long enough, cancels coast
void MotorController::brk(){
  AI1=1;
  AI2=1;
  digitalWrite(pinAI1, AI1);
  digitalWrite(pinAI2, AI2);
  delay(400);
  AI1=0;
  AI2=0;
  digitalWrite(pinAI1, AI1);
  digitalWrite(pinAI2, AI2);
  delay(600);
}

//clock-wise, anti clock-wise
void MotorController::cw(){
  AI1 = 1;
  AI2 = 0;
  digitalWrite(pinAI1, AI1);
  digitalWrite(pinAI2, AI2);
}
void MotorController::ccw(){
  AI1 = 0;
  AI2 = 1;
  digitalWrite(pinAI1, AI1);
  digitalWrite(pinAI2, AI2);
}
void MotorController::setDirection(int direction){
  if (direction){
    cw();
  } else{
    ccw();
  }
};

void MotorController::setSpeed(char pwmValue){
  // set an initial value for the PWM value
  analogWrite(pinPWM,pwmValue);
};