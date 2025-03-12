#include <Servo.h>

Servo S1;
Servo S2;
Servo S3;


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



unsigned long timestamp;
unsigned long elapsed;
unsigned long controlRate = 15;


 float S1RadAngle;
 float S2RadAngle;

const byte S1pwm = 53;  
const byte S2pwm = 51;  
const byte S3pwm = 49; 

int s0 = 3, s1 = 4, s2 = 5, s3 = 6;
int out = 7;
volatile unsigned int countR = 0, countG = 0, countB = 0;

int S1PulseWidth;
int S2PulseWidth;

int whiteCount = 0;
int greenCount = 0;
bool whiteSection = false;



void setup() {
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
    S3.write(0);

  //Serial.begin(9600);
  
  timestamp = millis();


}





void storePosition(){

        S1PulseWidth = moveServo(S1, 1424, -0.6);
        S2PulseWidth = moveServo(S2, 2000, -1.1);
        delay(1000);

}



void dropPen(){


    S1PulseWidth = moveServo(S1, 1424, 1);
    S2PulseWidth = moveServo(S2, 2000, -1);
    delay(1000);
    S3.write(90);
delay(150);


}





void drawLine(){
    elapsed = millis() - timestamp;

    if ( elapsed > controlRate ) {
        
        S1PulseWidth = moveServo(S1, 1424, 0.486584700);
        S2PulseWidth = moveServo(S2, 2000, -0.331055526);
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
  


  unsigned int readColor() {
      unsigned int pulse = pulseIn(out, LOW, 30000); 
      return (pulse == 0) ? 1 : pulse;
      // This code was taken from the data sheet for the colour sensor
  }
  

  bool IsItGreen() {
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




void loop() {
}


int moveServo(Servo servo, int refPulseWidth, float servoRadAngle){
  const float Pi = 3.142;
  float minPulseWidth = float(refPulseWidth)-1000.0;
  int cmdSignal = (servoRadAngle+(Pi/2))*(2000.0/Pi)+minPulseWidth;
  servo.writeMicroseconds(cmdSignal);
  return cmdSignal;
}

