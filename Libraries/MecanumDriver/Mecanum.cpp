#include <Arduino.h>
#include <Mecanum.h>

void Mecanum::begin() {

	Moto_Shield.begin();

	// Initialize the motors
	for (int i = 0; i < 4; i++) {
		motors[i] = Moto_Shield.getMotor(i+1);
	}
}

void Mecanum::WriteDirect(int motor1, int motor2, int motor3, int motor4)
{
	motors[0]->run((motor1 > 0) ? FORWARD : BACKWARD);
	motors[1]->run((motor2 > 0) ? FORWARD : BACKWARD);
	motors[2]->run((motor3 > 0) ? FORWARD : BACKWARD);
	motors[3]->run((motor4 > 0) ? FORWARD : BACKWARD);

	motors[0]->setSpeed(abs(motor1));
	motors[1]->setSpeed(abs(motor2));
	motors[2]->setSpeed(abs(motor3));
	motors[3]->setSpeed(abs(motor4));
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
		magnitude*sin(angle + PI_4) + rotation,
		magnitude*cos(angle+PI_4)-rotation,
		magnitude*cos(angle+PI_4)+rotation,
		magnitude*sin(angle+PI_4)-rotation
	};

	// Keep voltages in range of [-1, 1]
	for (int i = 0; i < 4; i++)
	{
		if (voltages[i] > 1 || voltages[i] < -1)
		{
			double scale = abs(voltages[i]);

			for (int j = 0; j < 4; j++)
			{
				voltages[j] /= scale;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		// Scale the voltage
		voltages[i] *= SCALE;

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
