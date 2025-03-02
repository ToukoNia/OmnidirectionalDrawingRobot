#include "ultrasonic.h"
void Ultrasonic::setup(int tPin, int ePin){
  trigPin=tPin;
  echoPin=ePin;
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

float Ultrasonic::calculateDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = distance * 0.034 / 2;  //called it distance twice to save storage and float operations
  return distance;
}