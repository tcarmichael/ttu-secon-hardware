#include "Arduino.h"
#include "Wire.h"
#include "mecanumControl.h"

mecanumControl::mecanumControl(){
  for(int i=1; i<=4; i++){
    point_moto[i-1] = Moto_Shield.getMotor(i);
  }
}

// input magnitude has to be between -1 and 1
// input angle has to be between 0 and 2 PI
// input rotation has to be between -1 and 1
void mecanumControl::mecanumControl(float magnitude, float angle, float rotation) {
  
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
  float VN[4];
  
  VN[0] = V1 * (255 / 2.0f);
  VN[1] = V2 * (255 / 2.0f);
  VN[2] = V3 * (255 / 2.0f);
  VN[3] = V4 * (255 / 2.0f); 
    
  // send the voltages to the motor driver
  for(int i=0; i<4; i++){
    if(VN[i] = 0){
	  //point_moto[i]->setSpeed(abs(VN[i]));
      point_moto[i]->run(RELEASE);
    }
    else if(VN[i] > 0){
	  point_moto[i]->setSpeed(abs(VN[i]));
      point_moto[i]->run(FORWARD);
    }
    else{
	  point_moto[i]->setSpeed(abs(VN[i]));
      point_moto[i]->run(REVERSE);
    }
  }
}
