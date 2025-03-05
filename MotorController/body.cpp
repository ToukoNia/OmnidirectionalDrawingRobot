#include "body.h"
void RobotBody::Setup(){
  base.setupPins(150);
}
void RobotBody::StartSequence(){
  base.calculateTrajectory(1,1);
 // base.findWall(20,15,0,1);
}
void RobotBody::FirstTunnel(){
//  base.findWall(20,20,1,0);
}

//void RobotBody::
