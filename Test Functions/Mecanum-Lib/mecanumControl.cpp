#include "Arduino.h"
#include "Wire.h"
#include "mecanumControl.h"

mecanumControl::mecanumControl(){
	Moto_Shield.begin();
}

// input magnitude has to be between -1 and 1
// input angle has to be between 0 and 2 PI
// input rotation has to be between -1 and 1
void mecanumControl::mecRun(float magnitude, float angle, float rotation) {
  
  // Wheel 1 is front left, wheel 2 is front right
  // Wheel 3 is rear left, wheel4 is rear right
  // Voltage multiplier for each wheels.
  float V1, V2, V3, V4;
  
  // Calculating the voltage multiplier
  V1 = magnitude*sin(angle+PI_4)+rotation;
  V2 = magnitude*cos(angle+PI_4)-rotation;
  V3 = magnitude*cos(angle+PI_4)+rotation;
  V4 = magnitude*sin(angle+PI_4)-rotation;

/*  
   float largest = 0;
  
  if(abs(V1) > largest){
    largest = V1;
  }
  
  if(abs(V2) > largest){
    largest = V2;
  }
  
  if(abs(V3) > largest){
    largest = V3;
  }
  
  if(abs(V4) > largest){
    largest = V4;
  }
*/
  // Normalizing the voltage multiplier for the motor outputs
  float VN1, VN2, VN3, VN4;
  
  VN1 = V1 * (255 / 2.0f);
  VN2 = V2 * (255 / 2.0f);
  VN3 = V3 * (255 / 2.0f);
  VN4 = V4 * (255 / 2.0f); 
    
  // send the voltages to the motor driver
  // to motor1
  if(VN1 = 0){
	//motor1->setSpeed(abs(VN1));
    motor1->run(RELEASE);
  }
  else if(VN1 > 0){
	motor1->setSpeed(abs(VN1));
    motor1->run(FORWARD);
  }
  else{
    motor1->setSpeed(abs(VN1));
    motor1->run(BACKWARD);
  }
  
  // to motor2
  if(VN2 = 0){
	//motor2->setSpeed(abs(VN2));
    motor2->run(RELEASE);
  }
  else if(VN2 > 0){
	motor2->setSpeed(abs(VN2));
    motor2->run(FORWARD);
  }
  else{
    motor2->setSpeed(abs(VN2));
    motor2->run(BACKWARD);
  }
	
  // to motor3
  if(VN3 = 0){
	//motor3->setSpeed(abs(VN3));
    motor3->run(RELEASE);
  }
  else if(VN3 > 0){
	motor3->setSpeed(abs(VN3));
    motor3->run(FORWARD);
  }
  else{
    motor3->setSpeed(abs(VN3));
    motor3->run(BACKWARD);
  }
  
  // to motor4
  if(VN4 = 0){
	//motor4->setSpeed(abs(VN4));
    motor4->run(RELEASE);
  }
  else if(VN4 > 0){
	motor4->setSpeed(abs(VN4));
    motor4->run(FORWARD);
  }
  else{
    motor4->setSpeed(abs(VN4));
    motor4->run(BACKWARD);
  }
}
