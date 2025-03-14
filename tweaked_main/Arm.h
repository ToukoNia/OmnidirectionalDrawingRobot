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
      0.438127303653856, 0.381915733628728, 0.338908141400432, 0.303742286927308, 0.274007528419744, 0.248379211915501, 0.226040948302631, 0.206450777344077, 0.189229907788622, 0.174103600940051, 0.160867112863193, 0.149364813017979, 0.139476729307019, 0.131109516225248, 0.124190178132831, 0.118661573211339, 0.114479104082869, 0.111608219557551, 0.110022482498407, 0.109702039489508, 0.110632379429415, 0.112803301880396, 0.116208038680366, 0.12084248797679, 0.126704530935137, 0.133793409462157, 0.142109149364637, 0.151652018088622, 0.162422009980026, 0.174418355154079, 0.187639050734562, 0.202080415527657, 0.217736671179309, 0.234599554538942, 0.252657967297152, 0.271897669942144, 0.292301027640874, 0.313846815747997, 0.336510092240437, 0.360262143449067
    };
    float S2Array[40] = {
      -0.403054157129073, -0.523962914097657, -0.621470080174836, -0.705289182237283, -0.779801704825698, -0.847426624890617, -0.909664274657929, -0.967518997793568, -1.02170030611054, -1.07272977717974, -1.12100263454673, -1.16682548586578, -1.21044061288807, -1.2520422426521, -1.29178781512826, -1.32980600848672, -1.36620259514576, -1.40106480657709, -1.43446464879017, -1.46646146455706, -1.49710394560128, -1.5264317373159, -1.5544767380043, -1.58126416691611, -1.60681345603178, -1.63113900682989, -1.6542508433443, -1.67615518549614, -1.69685496117259, -1.71635027128013, -1.7346388186518, -1.75171630897915, -1.76757682969223, -1.7822132108052, -1.79561737010128, -1.80778064360302, -1.81869410103752, -1.82834884495454, -1.83673629129525, -1.84384842855129
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