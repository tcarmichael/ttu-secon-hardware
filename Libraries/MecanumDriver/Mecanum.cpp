#include <Arduino.h>
#include <Mecanum.h>

void Mecanum::begin() {

	Moto_Shield.begin();

	// Initialize the motors
	for (int i = 0; i < 4; i++) {
		motors[i] = Moto_Shield.getMotor(i+1);
	}
}

// input magnitude has to be between -1 and 1
// input angle has to be between 0 and 2 PI
// input rotation has to be between -1 and 1
void Mecanum::mecRun(double magnitude, double angle, double rotation) {
  // Wheel 1 is front left, wheel 2 is front right
  // Wheel 3 is rear left, wheel4 is rear right
  // Voltage multiplier for each wheels.
  
  // Calculating the voltage multiplier
	double voltages[4] = {
		magnitude*sin(angle+PI_4)+rotation,
		magnitude*cos(angle+PI_4)-rotation,
		magnitude*cos(angle+PI_4)+rotation,
		magnitude*sin(angle+PI_4)-rotation
	};

	for (int i = 0; i < 4; i++) {
		// Scale the voltage
		voltages[i] *= SCALE;

		// Bounds-checking
		voltages[i] = (voltages[i] > 255) ? 255 : voltages[i];
		voltages[i] = (voltages[i] < -255) ? -255 : voltages[i];

		// Set the direction of the motor
		if (voltages[i] > 0) {
			motors[i]->run(FORWARD);
		} else if (voltages[i] < 0) {
			motors[i]->run(BACKWARD);
		}

		// Set the motor speed
		motors[i]->setSpeed(abs(voltages[i]));
	}
}
