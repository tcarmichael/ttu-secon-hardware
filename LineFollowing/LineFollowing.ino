#include <Wire.h>

#include <QTRSensors.h>
#include <Adafruit_MotorShield.h>

const double PI_4 = 0.78539816;
const int followerOffset = 3500;

// PID constants
const double Kp = 0.5f / followerOffset; // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
const double Kd = 0.001f; // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd)

// Line follower connections
const int NUM_SENSORS = 8;     // number of sensors used
const int EMITTER_PIN = 40;     // emitter is controlled by digital pin 2
unsigned char SENSOR_PINS[] = {22,24,26,28,30,32,34,36};
const unsigned int TIMEOUT = 2000;

QTRSensorsRC qtrrc(SENSOR_PINS, NUM_SENSORS, TIMEOUT);

Adafruit_MotorShield motorShield = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = motorShield.getMotor(1);
Adafruit_DCMotor *motor2 = motorShield.getMotor(2);
Adafruit_DCMotor *motor3 = motorShield.getMotor(3);
Adafruit_DCMotor *motor4 = motorShield.getMotor(4);

// input magnitude has to be between -1 and 1
// input angle has to be between 0 and 2 PI
// input rotation has to be between -1 and 1
void mecRun(double magnitude, double angle, double rotation) {
  
  // Wheel 1 is front left, wheel 2 is front right
  // Wheel 3 is rear left, wheel4 is rear right
  // Voltage multiplier for each wheels.
  double V1, V2, V3, V4;
  
  // Calculating the voltage multiplier
  V1 = magnitude*sin(angle+PI_4)+rotation;
  V2 = magnitude*cos(angle+PI_4)-rotation;
  V3 = magnitude*cos(angle+PI_4)+rotation;
  V4 = magnitude*sin(angle+PI_4)-rotation;
  
  // Normalizing the voltage multiplier for the motor outputs
  double VN1, VN2, VN3, VN4;
  
  VN1 = 255 * V1;
  VN2 = 255 * V2;
  VN3 = 255 * V3;
  VN4 = 255 * V4;
  
  VN1 = (VN1 > 255) ? 255 : VN1;
  VN2 = (VN2 > 255) ? 255 : VN2;
  VN3 = (VN3 > 255) ? 255 : VN3;
  VN4 = (VN4 > 255) ? 255 : VN4;
  
  VN1 = (VN1 < -255) ? -255 : VN1;
  VN2 = (VN2 < -255) ? -255 : VN2;
  VN3 = (VN3 < -255) ? -255 : VN3;
  VN4 = (VN4 < -255) ? -255 : VN4;
    
  // send the voltages to the motor driver
  // to motor1
  if(VN1 == 0){
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
  if(VN2 == 0){
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
  if(VN3 == 0){
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
  if(VN4 == 0){
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
  
  Serial.print(VN1);Serial.print(' ');
  Serial.print(VN2);Serial.print(' ');
  Serial.print(VN3);Serial.print(' ');
  Serial.print(VN4);Serial.print(' ');
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting calibration");
  
  // Calibrate the line-following sensor
  delay(500);
  
  for (int i = 0; i < 400; i++) {
    qtrrc.calibrate();
  }
  digitalWrite(13, LOW); // turn off the built-in LED
  
  // Print the calibration minimum and maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print("Min: ");
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(" Max: ");
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.println();
  }

	motorShield.begin();
} 

int lastError = 0;

void loop() {
	// Get line follower readings
	unsigned int sensors[NUM_SENSORS];
	int position = qtrrc.readLine(sensors, QTR_EMITTERS_ON, 1);

	// Calculate the error
	// Positive error is to the left; negative error is to the right
	int error = position - followerOffset;

	// Convert the error into a motor speed
	double motorSpeed = Kp * error + Kd * (error - lastError);

	lastError = error;

motorSpeed = (motorSpeed > 1) ? 1 : motorSpeed;
motorSpeed = (motorSpeed < -1) ? -1 : motorSpeed;
        mecRun(0.75, 0, motorSpeed);
        
        Serial.print(position);
        Serial.print(' ');
        Serial.print(error);
        Serial.print(' ');
        Serial.print(motorSpeed);
        Serial.println();
}
