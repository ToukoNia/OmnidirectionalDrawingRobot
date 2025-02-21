#include "OmnidirectionalController.h"
void OmnidirectionalController::setupPins(unsigned int systemSpeed){
  Motors[0].setupPins(12,11,10,13); //PinA1, PinA2, PinPWM, PinStandby
  Motors[1].setupPins(5,4,3,6); //PinA1, PinA2, PinPWM, PinStandby
  Motors[2].setupPins(7,8,9,6);  //PinA1, PinA2, PinPWM, PinStandby
  sysSpeed=systemSpeed;
}

void OmnidirectionalController::calculateTrajectory(float x,float y){ //uses the IK (without rotation) to allow for a 2d vector input to translate it to motor speeds
  for (i=0;i<3;i++){
    motorVector=(-sineVal[i]*x+cosVal[i]*y);
    motorVector=round(motorVector*sysSpeed);
    if (motorVector<0){
      motorVector=-motorVector;
      Motors[i].setDirection(0); //sets to counter clockwise
    } else {
      Motors[i].setDirection(1);  //sets to clockwise
    }
    Motors[i].setSpeed(motorVector);
  }
}

void OmnidirectionalController::Rotate(int w){  //precise turning
  //enc count for 1 rotation calculation
  //formula for in degrees = distanceWheel*encCount(960)/(360*wheelRadius)*w
  target=round(EncoderVal*w);
  Motors[0].setDirection(0);
  Motors[1].setDirection(0);
  Motors[2].setDirection(0);
  Motors[0].setSpeed(sysSpeed);
  Motors[1].setSpeed(sysSpeed);
  Motors[2].setSpeed(sysSpeed);
  encCount=i=0;
  while (1){
    if ((digitalRead(encPinA)&&!i)){
      encCount++;
      i=1;
    } else if (!digitalRead(encPinA)){
      i=0;
    }
    if (encCount>=target){
       break;
    }
 
  }
  calculateTrajectory(0,0);
}

/*
void OmnidirectionalController::staticDistance(int targetDistance){
  //code to read in from ultrasonic=readin
  int readIn; //
  if (readIn<=0.9*targetDistance || readIn>=1.1*targetDistance){
    calculateTrajectory((readIn-targetDistance)/(targetDistance+readIn),1,0); //might need to flip this if vertical and horizontal gets flipped
  } else{
    calculateTrajectory(1,0,0);
  }
}*/