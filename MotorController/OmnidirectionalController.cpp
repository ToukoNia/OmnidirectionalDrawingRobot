#include "OmnidirectionalController.h"
void OmnidirectionalController::setupPins(unsigned int systemSpeed){
  Motors[0].setupPins(12,11,10,13); //PinA1, PinA2, PinPWM, PinStandby
  Motors[1].setupPins(7,8,9,6);  //PinA1, PinA2, PinPWM, PinStandby
  Motors[2].setupPins(5,4,3,6); //PinA1, PinA2, PinPWM, PinStandby
  sysSpeed=systemSpeed;
}

void OmnidirectionalController::calculateTrajectory(float x,float y){ //uses the IK (without rotation) to allow for a 2d vector input to translate it to motor speeds
  value=sqrt(sq(x)+sq(y));
  x=x/value;
  y=y/value;
  for (i=0;i<3;i++){
    motorVector=(-sineVal[i]*x+cosVal[i]*y);
    if (!motorVector){
      Motors[i].coast();
    } else{
      motorVector=round(motorVector*sysSpeed);
      /* adds an offset to prevent the drifting issue
        if ((x&&y)&&(x<y)){
          motorVector=motorVector+x*sysSpeed/10
      }
      */

      if (motorVector<0){
        motorVector=-motorVector;
        Motors[i].setDirection(0); //sets to counter clockwise
      } else {
        Motors[i].setDirection(1);  //sets to clockwise
      }
      Motors[i].setSpeed(motorVector);
    }
  }
}

void OmnidirectionalController::Rotate(int w){  //precise turning
  //enc count for 1 rotation calculation
  //formula for in degrees = distanceWheel*encCount(960)/(360*wheelRadius)*w
  value=round(EncoderVal*w);
  Motors[0].setDirection(1);
  Motors[1].setDirection(1);
  Motors[2].setDirection(1);
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
  calculateTrajectory(0,0);
}

void OmnidirectionalController::brk(){
  for (i=0;i<3;i++){
    Motors[i].brk();
  }
}
