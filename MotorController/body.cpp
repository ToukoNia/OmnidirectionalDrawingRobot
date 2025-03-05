#include "body.h"
void RobotBody::Setup(){
  base.setupPins(150);
  Ultrasonics[0].setup(25,27);  //trigPin, echoPin
  Ultrasonics[1].setup(29,31);  //right ultrasonic
//  base.Rotate(180);
}
void RobotBody::StartSequence(){
  findWall(20,10,0,1,1);
}
void RobotBody::FirstTunnel(){
  findWall(20,10,1,0,1);
 // base.Rotate(90);
}


void RobotBody::staticDistance(int targetDistance, bool sideDirection,int robotDirection){
  distance=round(Ultrasonics[sideDirection].calculateDistance());
    if (distance<=0.9*targetDistance || distance>=1.1*targetDistance){  //have a way to flip which trajectory mayb?
      if (sideDirection){
        base.calculateTrajectory(robotDirection,0.75*(targetDistance-distance)/(targetDistance)); //might need to flip this if vertical and horizontal gets flipped, or add a proportional control
      } else {
        base.calculateTrajectory((distance-targetDistance)/(targetDistance),-robotDirection);
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
    while(Ultrasonics[forwardDirection].calculateDistance()>targetDistance){
      staticDistance(constantDistance,sideDirection,1);
   }
  } else {
    while(Ultrasonics[forwardDirection].calculateDistance()<targetDistance){
      staticDistance(constantDistance,sideDirection,-1);
   }
  }

   base.calculateTrajectory(0,0);
   base.breakAll();
   return 0;
}