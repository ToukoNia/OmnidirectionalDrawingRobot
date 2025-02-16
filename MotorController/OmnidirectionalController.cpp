#include "OmnidirectionalController.h"
void OmnidirectionalController::setupPins(unsigned int systemSpeed){
  Motors[0].setupPins(12,11,10,13); //PinA1, PinA2, PinPWM, PinStandby
  Motors[1].setupPins(5,4,3,6); //PinA1, PinA2, PinPWM, PinStandby
  Motors[2].setupPins(7,8,9,6);  //PinA1, PinA2, PinPWM, PinStandby
  sysSpeed=systemSpeed;
}

void OmnidirectionalController::calculateTrajectory(float x,float y, float w){
  for (int i=0;i<3;i++){
    motorVector=(-sineVal[i]*x+cosVal[i]*y+w);
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