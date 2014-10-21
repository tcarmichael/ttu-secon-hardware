#ifndef mecanumControl_h
#define mecanumControl_h

#include <Wire.h>
#include "../Adafruit_MotorShield/Adafruit_MotorShield.h"
//#include "utility/Adafruit_PWMServoDriver.h"

//#define PI 3.14159265
#define PI_4 0.78539816

class mecanumControl
{
	public:
		mecanumControl();
		void mecRun(float magnitude, float angle, float rotation); 
	private:
		Adafruit_MotorShield Moto_Shield = Adafruit_MotorShield();
		Adafruit_DCMotor *motor1 = Moto_Shield.getMotor(1);
		Adafruit_DCMotor *motor2 = Moto_Shield.getMotor(2);
		Adafruit_DCMotor *motor3 = Moto_Shield.getMotor(3);
		Adafruit_DCMotor *motor4 = Moto_Shield.getMotor(4);
};
#endif
