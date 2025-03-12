#ifndef Arm_h
#define Arm_h
#include <Servo.h>
#include <Arduino.h>


class Arm { 
  private:
    float S1Array[40] = {
      0.486584700, 0.420641037, 0.373101659, 0.335241481, 0.303708188,
      0.276795530, 0.253499224, 0.233172613, 0.215373271, 0.199785185,
      0.186175429, 0.174368302, 0.164229014, 0.155652931, 0.148558206,
      0.142880574, 0.138569561, 0.135585656, 0.133898142, 0.133483401,
      0.134323552, 0.136405326, 0.139719128, 0.144258222, 0.150018019,
      0.156995432, 0.165188290, 0.174594793, 0.185212999, 0.197040343,
      0.210073184, 0.224306373, 0.239732859, 0.256343320, 0.274125840,
      0.293065618, 0.313144743, 0.334342011, 0.356632815, 0.379989095
    };
    float S2Array[40] = {
      -0.331055526, -0.469694203, -0.575532848, -0.664357530, -0.742250642,
      -0.812320347, -0.876406087, -0.935700876, -0.991028577, -1.042984609,
      -1.092014279, -1.138459522, -1.182588360, -1.224614291, -1.264709532,
      -1.303014327, -1.339643673, -1.374692293, -1.408238371, -1.440346427,
      -1.471069562, -1.500451226, -1.528526654, -1.555324029, -1.580865455,
      -1.605167770, -1.628243249, -1.650100211, -1.670743562, -1.690175276,
      -1.708394841, -1.725399669, -1.741185480, -1.755746661, -1.769076613,
      -1.781168076, -1.792013434, -1.801605006, -1.809935317, -1.816997349
    };

    Servo S1;
    Servo S2;
    Servo S3;

    unsigned long timestamp;
    unsigned long elapsed;
    unsigned long controlRate = 15;

    float S1RadAngle;
    float S2RadAngle;

    const byte S1pwm = 53;  
    const byte S2pwm = 51;  
    const byte S3pwm = 49; 

    int s0 = 47, s1 = 45, s2 = 41, s3 = 39;
    int out = 43;
    volatile unsigned int countR = 0, countG = 0, countB = 0;

    int S1PulseWidth;
    int S2PulseWidth;

    int whiteCount = 0;
    int greenCount = 0;
    bool whiteSection = false;
    
    unsigned int readColor();
    bool IsItGreen();
    int moveServo(Servo servo, int refPulseWidth, float servoRadAngle);
  public:
    void Setup();
    void storePosition();
    void dropPen();
    void drawLine();

};

#endif