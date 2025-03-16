#include "body.h"
void RobotBody::Setup(){
  base.setupPins(125);
  base.Rotate(180);
}

void RobotBody::StartSequence(){
  
  findWall(17,16,0,1,1);  //endponint in cm, how far from wall in cm, if sideways is now forwards, if forwards is now sideways, direction
  base.Rotate(90);
  delay(100);
  findWall(10,17,0,1,1);
  delay(100);
}


void RobotBody::FinalStretch(){
  findWall(13,17,0,1,0);
  delay(100);
  findWall(82,13,1,0,0);
  findWall(80,82,0,1,0);
}

void RobotBody::staticDistance(int targetDistance, bool sideDirection,int robotDirection){
  distance=Ultrasonics[sideDirection].ping_cm();
  error=K*(targetDistance-distance);
  if ((distance<=targetDistance+DISTANCE_BUFFER || distance>=DISTANCE_BUFFER+targetDistance)&&(distance>targetDistance-7)&&distance){  
      if (sideDirection){
        base.calculateTrajectory(robotDirection,error); 
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
  distance=Ultrasonics[forwardDirection].ping_cm();
  if (robotOrientation){
    while((distance>targetDistance)||!distance){
      staticDistance(constantDistance,sideDirection,1);
      distance=Ultrasonics[forwardDirection].ping_cm();
   }
  } else {
    while(Ultrasonics[forwardDirection].convert_cm(Ultrasonics[forwardDirection].ping_median(5))<targetDistance){
      staticDistance(constantDistance,sideDirection,-1);
   }
  }
  base.brk();
}