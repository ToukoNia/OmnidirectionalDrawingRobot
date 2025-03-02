#include "body.h"

void RobotBody::StartSequence(){
  movement.setupPins(150);
  movement.Rotate(180);
  movement.calculateTrajectory(0,1);
  lineDetector.detectLine();
  LineFollowing(BLACK);
}
void RobotBody::LineFollowing(int colour){
  if (lineDetector.readSensors(colour)){
    lineDetector.assignAngle();
  } 
  movement.calculateTrajectory(lineDetector.x,lineDetector.y);
}