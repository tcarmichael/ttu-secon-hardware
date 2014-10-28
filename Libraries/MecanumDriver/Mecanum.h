#ifndef Mecanum_h
#define Mecanum_h

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Pi / 4
// Used for the wheel rotation formulas
const double PI_4 = 0.78539816;


class Mecanum
{
	public:
		Mecanum();
		void mecRun(double magnitude, double angle, double rotation);

	private:
		Adafruit_MotorShield Moto_Shield;
		Adafruit_DCMotor *motors[4];

		// Scales the motor shield signal from [-2, 2] to [-255, 255]
		static const int SCALE = 128;
};
#endif
