#ifndef Mecanum_h
#define Mecanum_h

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Pi / 4
// Used for the wheel rotation formulas
const double PI_4 = PI/4;


class Mecanum
{
	public:
		Mecanum() {};
		void mecRun(double magnitude, double angle, double rotation);
		void begin();
		void WriteDirect(int, int, int, int);

	private:
		Adafruit_MotorShield Moto_Shield;
		Adafruit_DCMotor *motors[4];

		// Scales the motor shield signal from [-1, 1] to [-255, 255]
		static const int SCALE = 255;
};
#endif
