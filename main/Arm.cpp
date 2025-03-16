#include "Arm.h"


void Arm::Setup() {
  S1.attach(S1pwm);  
  S2.attach(S2pwm);  
  S3.attach(S3pwm);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);  
  digitalWrite(s1, LOW);   
  S3.write(90);

  storePosition();
}

void Arm::storePosition(){
  moveServo(S1, 1424, -0.8);
  moveServo(S2, 2000, -2.4);
  delay(100);
}

void Arm::dropPen(){
  moveServo(S1, 1424, 0.4);
  S3.write(180);
  moveServo(S2, 2000, -1.7);
  delay(1000);
  delay(1000);
  storePosition();
}

void Arm::drawLine(){
  RateLimitServo(S2, 2000, S2_BASE,-0.331055526);
  RateLimitServo(S1, 1424, S1_BASE, 0.486584700);
  delay(2000);
  
    for (int i = 0; i < 40; i++) {
      S1RadAngle = S1Array[i];
      S2RadAngle = S2Array[i];
          
      GreenCheck = IsItGreen();
      if(GreenCheck == false){
          //Serial.println("White/n");
          whiteCount++;
          if(whiteCount>3){
            greenCount=0;
          }
          if(whiteCount>10){
          whiteSection=true;
          }
      }
      else{
          //Serial.println("Green/n");
          greenCount++;
          if(greenCount>3){
            whiteCount=0;
          }
          if(greenCount>7 && whiteSection==true){
            break;
          }
      }
      moveServo(S1, 1424, S1RadAngle);
      moveServo(S2, 2000, S2RadAngle);
      delay(150);
  }
  storePosition();
}


unsigned int Arm::readColor() {
    unsigned int pulse = pulseIn(out, LOW, 30000); 
    return (pulse == 0) ? 1 : pulse;
    // This code was taken from the data sheet for the colour sensor
}
  
bool Arm::IsItGreen() {
    digitalWrite(s2, LOW); digitalWrite(s3, LOW);
    countR = readColor();
    if (countR>50) { 
        return true;
    } else {
        return false;
    }
}

int Arm::moveServo(Servo servo, int refPulseWidth, float servoRadAngle){
  float minPulseWidth = float(refPulseWidth)-1000.0;
  int cmdSignal = (servoRadAngle+(Pi/2))*(2000.0/Pi)+minPulseWidth;
  servo.writeMicroseconds(cmdSignal);
  return cmdSignal;
}

void Arm::RateLimitServo(Servo servo, int refPulseWidth, float currentAngle, float servoRadAngle){
  while (currentAngle!=servoRadAngle){
    currentAngle=increment(currentAngle, servoRadAngle);
    moveServo(servo, refPulseWidth, currentAngle);
    delay(10);
  }
}

float Arm::increment(float currentAngle, float targetAngle){
  if (currentAngle>targetAngle){
    return max(currentAngle-INCREMENT,targetAngle);
  } else {
    return min(currentAngle+INCREMENT,targetAngle);
  }
}