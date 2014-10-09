//#define PI 3.14159265
#define PI_4.78539816

void setup(){

}

void loop(){

}

// input magnitude has to be between -1 and 1
// input angle has to be between 0 and 2 PI
// input rotation has to be between -1 and 1
void mecanumControl(float magnitude, float angle, float rotation) {
  
  // Wheel 1 is front left, wheel 2 is front right
  // Wheel 3 is rear left, wheel4 is rear right
  // Voltage multiplier for each wheels.
  float V1, V2, V3, V4;
  
  // Calculating the voltage multiplier
  V1 = magnitude*sin(angle+PI_4)+rotation;
  V2 = magnitude*cos(angle+PI_4)-rotation;
  V3 = magnitude*cos(angle+PI_4)+rotation;
  V4 = magnitude*sin(angle+PI_4)-rotation;
  
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
  
  // Normalizing the voltage multiplier for the motor outputs
  float V1N, V2N, V3N, V4N;
  
  V1N = V1 / largest;
  V2N = V2 / largest;
  V3N = V3 / largest;
  V4N = V4 / largest;
  
  // send the voltages to the motor driver
  // driveMotor(V1N, V2N, V3N, V4N);
}
