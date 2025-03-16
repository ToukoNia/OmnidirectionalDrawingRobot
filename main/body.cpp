#include "body.h"
void RobotBody::Setup(){
  base.setupPins(125);
  base.Rotate(180);
}

void RobotBody::StartSequence(){
  
  findDistance(0);
  findWall(18,16,0,1,1);  //endponint in cm, how far from wall in cm, if sideways is now forwards, if forwards is now sideways, direction
  base.Rotate(95);
  delay(100);
  findDistance(1);
  findWall(13,18,0,1,1);
  delay(100);
}


void RobotBody::FinalStretch(){
  delay(100);
  findWall(lengths[0]+2,13,1,0,0);
  findWall(lengths[1],lengths[0]+2,0,1,0);
}

void RobotBody::findDistance(bool direction){
  lengths[direction]=Ultrasonics[0].convert_cm(Ultrasonics[0].ping_median(5));
}

void RobotBody::staticDistance(int targetDistance, bool sideDirection,int robotDirection){
  distance=Ultrasonics[sideDirection].ping_cm();
  error=K*(targetDistance-distance)/10;
  error=abs(error)>0.5 ? error*0.5/abs(error) : error;
    if ((distance<=targetDistance+DISTANCE_BUFFER || distance>=DISTANCE_BUFFER+targetDistance)&&distance){  //have a way to flip which trajectory mayb?
      if (sideDirection){
        base.calculateTrajectory(robotDirection,error); //might need to flip this if vertical and horizontal gets flipped, or add a proportional control
      } else {
        base.calculateTrajectory(-error,-robotDirection);
      }
    } else {
      if (sideDirection){
        base.calculateTrajectory(robotDirection,0);
      } else {
        base.calculateTrajectory(0,-robotDirection);
      }
    
    }
}

void RobotBody::findWall(int targetDistance, int constantDistance, bool forwardDirection, bool sideDirection, bool robotOrientation){
  if (robotOrientation){
    while(Ultrasonics[forwardDirection].convert_cm(Ultrasonics[forwardDirection].ping_median(3))>targetDistance){
      staticDistance(constantDistance,sideDirection,1);
   }
  } else {
    while(Ultrasonics[forwardDirection].convert_cm(Ultrasonics[forwardDirection].ping_median(3))<targetDistance){
      staticDistance(constantDistance,sideDirection,-1);
   }
  }
  base.brk();
}