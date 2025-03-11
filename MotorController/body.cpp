#include "body.h"
void RobotBody::Setup(){
  base.setupPins(150);
  base.Rotate(180);
}

void RobotBody::StartSequence(){
  
  findDistance(0);
  findWall(19,16,0,1,1);  //endponint in cm, how far from wall in cm, if sideways is now forwards, if forwards is now sideways, direction
  base.Rotate(95);
  delay(100);
  findDistance(1);
  findWall(8,13,0,1,1);

}


void RobotBody::FinalStretch(){
  base.calculateTrajectory(-1,0);
  delay(300);
  findWall(lengths[0]+1,12,1,0,0);
  findWall(lengths[1],lengths[0]+1,0,1,0);
}

void RobotBody::findDistance(bool direction){
  lengths[direction]=Ultrasonics[0].convert_cm(Ultrasonics[0].ping_median(5));
}

void RobotBody::staticDistance(int targetDistance, bool sideDirection,int robotDirection){
  distance=Ultrasonics[sideDirection].convert_cm(Ultrasonics[sideDirection].ping_median(3));
    if ((distance<=targetDistance+DISTANCE_BUFFER || distance>=DISTANCE_BUFFER+targetDistance)&&distance){  //have a way to flip which trajectory mayb?
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