
#include <Servo.h>

const int NUM_SERVOS = 6;
const int FIRST_SERVO_PIN = 2;
Servo arm[NUM_SERVOS];
int starting[NUM_SERVOS]={90, 40, 50, 130, 90, 90};
void setup() {
  // Attach each servo in the arm
  for (int servoIndex = 0; servoIndex < NUM_SERVOS; servoIndex++) {
    arm[servoIndex].attach(servoIndex + FIRST_SERVO_PIN);
  }
  
  for (int servoIndex = 0; servoIndex < NUM_SERVOS; servoIndex++) 
     {
     arm[servoIndex].write(starting[servoIndex]);
     }
}


void loop() 
{
     
}
