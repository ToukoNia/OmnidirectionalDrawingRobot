#include "OmnidirectionalController.h"
void OmnidirectionalController::setupPins(unsigned int sysSpeed){
  Motors[1].setupPins(7,8,5,9); //PinA1, PinA2, PinPWM, PinStandby
  Motors[2].setupPins(0,0,0,0); //PinA1, PinA2, PinPWM, PinStandby
  Motors[3].setupPins(0,0,0,0);  //PinA1, PinA2, PinPWM, PinStandby
}

void OmnidirectionalController::calculateTrajectory(int x, int y, int w){
  x=sysSpeed*x;
  y=sysSpeed*y;
  for (int i=0;i<3;i++){
    motorVector=(-sineVal[i]*x+cosVal[i]*y+w*wheelDistance)/wheelRadius;
    if (motorVector<0){
      motorVector=-motorVector;
      Motors[i].setDirection(0); //sets to counter clockwise
    } else {
      Motors[i].setDirection(1);  //sets to clockwise
    }
    Motors[i].setSpeed(motorVector);
  }
}

void OmnidirectionalController::staticDistance(int targetDistance){
  //code to read in from ultrasonic=readin
  int readIn; //
  if (readIn<=0.9*targetDistance || readIn>=1.1*targetDistance){
    calculateTrajectory((readIn-targetDistance)/(targetDistance+readIn),1,0); //might need to flip this if vertical and horizontal gets flipped
  } else{
    calculateTrajectory(1,0,0);
  }
}