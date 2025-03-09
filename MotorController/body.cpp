#include "body.h"
void RobotBody::Setup(){
  base.setupPins(150);
  base.Rotate(180);
}

void RobotBody::StartSequence(){
  findWall(20,16,0,1,1);  //endponint in cm, how far from wall in cm, if sideways is now forwards, if forwards is now sideways, direction
  base.Rotate(100);
  delay(100);
  findWall(17,20,0,1,1);
}


void RobotBody::FinalStretch(){
  delay(20);
  findWall(83,15,1,0,0);
  findWall(80,83,0,1,0);
}



void RobotBody::staticDistance(int targetDistance, bool sideDirection,int robotDirection){
  distance=Ultrasonics[sideDirection].ping_cm();
    if ((distance<=0.8*targetDistance || distance>=1.2*targetDistance)&&distance){  //have a way to flip which trajectory mayb?
      if (sideDirection){
        base.calculateTrajectory(robotDirection,0.75*(targetDistance-distance)/(targetDistance)); //might need to flip this if vertical and horizontal gets flipped, or add a proportional control
      } else {
        base.calculateTrajectory(0.75*(distance-targetDistance)/(targetDistance),-robotDirection);
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
   base.calculateTrajectory(0,0);
}