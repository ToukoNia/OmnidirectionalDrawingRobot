#include "Arm.h"
#include <Servo.h>


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

  //Serial.begin(9600);
  
  timestamp = millis();
}

void Arm::storePosition(){
  S1PulseWidth = moveServo(S1, 1424, -0.8);
  S2PulseWidth = moveServo(S2, 2000, -2.4);
  delay(2000);
}

void Arm::dropPen(){
  S1PulseWidth = moveServo(S1, 1424, 0.6);
  S2PulseWidth = moveServo(S2, 2000, -2);
  delay(1000);
  S3.write(180);
  delay(1000);
}

void Arm::drawLine(){
    elapsed = millis() - timestamp;

    if ( elapsed > controlRate ) {
        S2PulseWidth = moveServo(S2, 2000, -0.331055526);
        delay(500);
        S1PulseWidth = moveServo(S1, 1424, 0.486584700);
        
        delay(2000);
        
        bool lineFinished=false;
        while(!lineFinished){
            for (int i = 0; i < 40; i++) {
                S1RadAngle = S1Array[i];
                S2RadAngle = S2Array[i];
                    
                bool GreenCheck = IsItGreen();
                if(GreenCheck == false){
                    //Serial.println("White/n");
                    whiteCount+=1;
                    if(whiteCount>3){
                    greenCount=0;
                    }
                    if(whiteCount>10){
                    whiteSection=true;
                    }
                }
                else{
                    //Serial.println("Green/n");
                    greenCount+=1;
                    if(greenCount>3){
                    whiteCount=0;
                    }
                    if(greenCount>7 && whiteSection==true){
                    lineFinished=true;
                    i = 40;
                    //Serial.print("line finished");
                    //delay(3000);
                    }
                }
                
                
                
                S1PulseWidth = moveServo(S1, 1424, S1RadAngle);
                S2PulseWidth = moveServo(S2, 2000, S2RadAngle);
                
                //Serial.print("White count =");
                //Serial.println(whiteCount);
                
                //Serial.print("Green count =");
                //Serial.println(greenCount);
                
                delay(150);
        }
        }
  
  
    }
  }

unsigned int Arm::readColor() {
    unsigned int pulse = pulseIn(out, LOW, 30000); 
    return (pulse == 0) ? 1 : pulse;
    // This code was taken from the data sheet for the colour sensor
}
  
bool Arm::IsItGreen() {
    digitalWrite(s2, LOW); digitalWrite(s3, LOW);
    countR = readColor();
    //Serial.print("Red: ");
    //Serial.println(countR);

    if (countR>50) { 
        //Serial.println("Detected: Green\n");
        return true;
    } else {
        //Serial.println("Detected: White\n");
        return false;
    }
    delay(100);
    // Some of this code was taken from the data sheet for the colour sensor
}

int Arm::moveServo(Servo servo, int refPulseWidth, float servoRadAngle){
  const float Pi = 3.142;
  float minPulseWidth = float(refPulseWidth)-1000.0;
  int cmdSignal = (servoRadAngle+(Pi/2))*(2000.0/Pi)+minPulseWidth;
  servo.writeMicroseconds(cmdSignal);
  return cmdSignal;
}