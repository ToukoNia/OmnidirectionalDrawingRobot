#include "body.h"
void RobotBody::Setup(){
  base.setupPins(PWM_VALUE);
 // base.Rotate(180);
}

void RobotBody::StartSequence(){
  
  findDistance(0);
  findWall(18,16,0,1,1);  //endponint in cm, how far from wall in cm, if sideways is now forwards, if forwards is now sideways, direction
  base.Rotate(95);
  delay(100);
  findDistance(1);
  findWall(8,18,0,1,1);

}


void RobotBody::FinalStretch(){
  base.calculateTrajectory(-1,0);
  delay(300);
  findWall(lengths[0]+DISTANCE_BUFFER,8,1,0,0);
  findWall(lengths[1],lengths[0]+DISTANCE_BUFFER,0,1,0);
}

void RobotBody::findDistance(bool direction){
  lengths[direction]=Ultrasonics[0].convert_cm(Ultrasonics[0].ping_median(5));
}

void RobotBody::staticDistance(int targetDistance, bool sideDirection,int robotDirection){
  distance=Ultrasonics[sideDirection].convert_cm(Ultrasonics[sideDirection].ping_median(5));
//  error=(targetDistance-distance)/10
    if ((distance<=targetDistance-DISTANCE_BUFFER || distance>=DISTANCE_BUFFER+targetDistance)&&!(distance<lastDistance-6)&&distance){  //have a way to flip which trajectory mayb?
      if (sideDirection){
        eIntegral=eIntegral+Ki*(targetDistance-distance)/10;
        //derivative=Kd*(error-2*e_n1+e_n2);
        piController=K*(targetDistance-distance)/10;
        base.calculateTrajectory(robotDirection,piController); //might need to flip this if vertical and horizontal gets flipped, or add a proportional control
      } else {
       eIntegral=eIntegral+Ki*(distance-targetDistance)/10;
        piController=K*(distance-targetDistance)/10;
        base.calculateTrajectory(piController,-robotDirection);
      }
    } else {
      if (sideDirection){
        base.calculateTrajectory(robotDirection,0);
      } else {
        base.calculateTrajectory(0,-robotDirection);
      }
    }

  //  e_n=
}

void RobotBody::findWall(int targetDistance, int constantDistance, bool forwardDirection, bool sideDirection, bool robotOrientation){
  eIntegral=0;
  if (robotOrientation){
    while(Ultrasonics[forwardDirection].convert_cm(Ultrasonics[forwardDirection].ping_median(5))>targetDistance){
      staticDistance(constantDistance,sideDirection,1);
   }
  } else {
    while(Ultrasonics[forwardDirection].convert_cm(Ultrasonics[forwardDirection].ping_median(5))<targetDistance){
      staticDistance(constantDistance,sideDirection,-1);
   }
  }
   base.calculateTrajectory(0,0);
}