#ifndef mecanumControl_h
#define mecanumControl_h 
//#define PI 3.14159265
#define PI_4 0.78539816
#include "Arduino.h"
#include <Wire.h>
#include "../Adafruit_MotorShield/Adafruit_MotorShield.h"
//#include "utility/Adafruit_PWMServoDriver.h"

class mecanumControl
{
	public:
		mecanumControl();
		void mecanumControl(float magnitude, float angle, float rotation); 
	private:
		Adafruit_MotorShield Moto_Shield = Adafruit_MotorShield();
		Adafruit_DCMotor *point_moto[] = {0,0,0,0};
}
#endif
