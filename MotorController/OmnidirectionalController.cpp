#include "OmnidirectionalController.h"
void OmnidirectionalController::setupPins(unsigned int systemSpeed){
  Motors[0].setupPins(12,11,10,13); //PinA1, PinA2, PinPWM, PinStandby
  Motors[1].setupPins(5,4,3,6); //PinA1, PinA2, PinPWM, PinStandby
  Motors[2].setupPins(7,8,9,6);  //PinA1, PinA2, PinPWM, PinStandby
  
  Ultrasonics[0].setup(1,2);
  Ultrasonics[1].setup(3,4);
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
  value=round(EncoderVal*w);
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
    if (encCount>=value){
       break;
    }
  }
  Motors[0].brk();
  Motors[1].brk();
  Motors[2].brk();
}

void OmnidirectionalController::staticDistance(int targetDistance, bool sideDirection){
    value=Ultrasonics[sideDirection].calculateDistance();
    if (value<=0.9*targetDistance || value>=1.1*targetDistance){  //have a way to flip which trajectory mayb?
      calculateTrajectory(1,(value-targetDistance)/(targetDistance)); //might need to flip this if vertical and horizontal gets flipped, or add a proportional control
    } else{
      calculateTrajectory(1,0);
    }
}

void OmnidirectionalController::findWall(int targetDistance, int constantDistance, bool forwardDirection, bool sideDirection){
   while(Ultrasonics[forwardDirection].calculateDistance()>targetDistance){
      staticDistance(constantDistance,sideDirection);
   }
   Motors[0].brk();
   Motors[1].brk();
   Motors[2].brk();
}
