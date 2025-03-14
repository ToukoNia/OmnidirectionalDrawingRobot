// MotorController.h
#ifndef MotorController_h
#define MOtorController_h

#include <Arduino.h>
class MotorController {
  private:
    byte pinAI1;
    byte pinAI2;
    byte pinPWM;
    byte pinStandBy;
    boolean AI1 = 0;            // AI1 pin value
    boolean AI2 = 0;            // AI2 pin value
    boolean standBy = 0;        // standBy pin Value
    boolean rotDirect = 0;      // Rotation direction
    unsigned char pwmValue = 0; // PWM value to be written to the output
    void cw();
    void ccw();
    

  public:
    void setupPins(byte inputPinA1, byte inputpinA2, byte inputPinPWM, byte inputPinStandby);
    void setSpeed(char pwmValue);
    void setDirection(int direction);
    void brk();
    void coast();
};
#endif