//body.h
#ifndef ultrasonic_h
#define ultrasonic_h
#include <arduino.h>
#define distanceCoeff 0.0343

class Ultrasonic { 
  private:
    int trigPin; int echoPin; float distance;
  public:
    void setup(int tPin, int ePin);
    float calculateDistance();
};
#endif