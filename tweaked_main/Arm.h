#ifndef Arm_h
#define Arm_h
#include <Servo.h>
#include <Arduino.h>
#define Pi 3.142
#define INCREMENT 0.0157
#define S1_BASE -0.8
#define S2_BASE -2.4

class Arm { 
  private:
    float S1Array[40] = { 
    0.4095,    0.3578,    0.3171,    0.2835,
    0.2547,    0.2299,    0.2081,    0.1889,
    0.1720,    0.1572,    0.1442,    0.1329,
    0.1231,    0.1149,    0.1080,    0.1026,
    0.0985,    0.0957,    0.0942,    0.0939,
    0.0949,    0.0971,    0.1005,    0.1052,
    0.1112,    0.1183,    0.1267,    0.1363,
    0.1472,    0.1593,    0.1726,    0.1872,
    0.2030,    0.2201,    0.2383,    0.2577,
    0.2784,    0.3001,    0.3231,    0.3471
    };
    float S2Array[40] = {
   -0.4444,   -0.5570,   -0.6501,   -0.7311,
   -0.8037,   -0.8699,   -0.9311,   -0.9881,
   -1.0415,   -1.0920,   -1.1398,   -1.1853,
   -1.2286,   -1.2699,   -1.3095,   -1.3473,
   -1.3836,   -1.4183,   -1.4516,   -1.4836,
   -1.5142,   -1.5435,   -1.5715,   -1.5983,
   -1.6239,   -1.6482,   -1.6714,   -1.6933,
   -1.7141,   -1.7336,   -1.7519,   -1.7691,
   -1.7850,   -1.7997,   -1.8131,   -1.8254,
   -1.8363,   -1.8460,   -1.8545,   -1.8616
    };

    Servo S1;
    Servo S2;
    Servo S3;

    float S1RadAngle;
    float S2RadAngle;

    const byte S1pwm = 53;  
    const byte S2pwm = 51;  
    const byte S3pwm = 49; 

    int s0 = 47, s1 = 45, s2 = 41, s3 = 39;
    int out = 43;
    volatile unsigned int countR = 0, countG = 0, countB = 0;

    int whiteCount = 0;
    int greenCount = 0;
    bool whiteSection = false; bool GreenCheck;
    
    unsigned int readColor();
    bool IsItGreen();
    int moveServo(Servo servo, int refPulseWidth, float servoRadAngle);
    void storePosition();
    float increment(float currentAngle, float targetAngle);
    void RateLimitServo(Servo servo, int refPulseWidth, float currentAngle, float servoRadAngle);
  public:
    void Setup();
    void dropPen();
    void drawLine();

};

#endif