#include <Arduino.h>
#include <Mecanum.h>

void Mecanum::begin() {

	Moto_Shield.begin();

	// Initialize the motors
	for (int i = 0; i < 4; i++) {
		motors[i] = Moto_Shield.getMotor(i+1);
	}

	// Initialize last directions and speeds
	WriteDirect(0, 0, 0, 0);

	// Initialize the angle
	set_angle(0);
}

void Mecanum::WriteDirect(int motor1, int motor2, int motor3, int motor4)
{
	_lastDir[0] = (motor1 > 0) ? FORWARD : BACKWARD;
	_lastDir[1] = (motor2 > 0) ? FORWARD : BACKWARD;
	_lastDir[2] = (motor3 > 0) ? FORWARD : BACKWARD;
	_lastDir[3] = (motor4 > 0) ? FORWARD : BACKWARD;
	motors[0]->run(_lastDir[0]);
	motors[1]->run(_lastDir[1]);
	motors[2]->run(_lastDir[2]);
	motors[3]->run(_lastDir[3]);

	_lastSpeed[0] = abs(motor1);
	_lastSpeed[1] = abs(motor2);
	_lastSpeed[2] = abs(motor3);
	_lastSpeed[3] = abs(motor4);
	motors[0]->setSpeed(_lastSpeed[0]);
	motors[1]->setSpeed(_lastSpeed[1]);
	motors[2]->setSpeed(_lastSpeed[2]);
	motors[3]->setSpeed(_lastSpeed[3]);
}

// input magnitude has to be between -1 and 1
// input angle has to be between 0 and 2 PI
// input rotation has to be between -1 and 1
void Mecanum::mecRun(double magnitude, double angle, double rotation) {
  // Wheel 1 is front left, wheel 2 is front right
  // Wheel 3 is rear left, wheel4 is rear right
  // Voltage multiplier for each wheels.

	if (angle != _angle)
	{
		set_angle(angle);
	}
  
  // Calculating the voltage multiplier
	double voltages[4] = {
		magnitude*_mag[0] + rotation,
		magnitude*_mag[1] - rotation,
		magnitude*_mag[2] + rotation,
		magnitude*_mag[3] - rotation
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
		uint8_t dir = (voltages[i] > 0) ? FORWARD : BACKWARD;
		if (dir != _lastDir[i]) {
			_lastDir[i] = dir;
			motors[i]->run(_lastDir[i]);
		}

		// Set the motor speed
		if (abs(voltages[i]) != _lastSpeed[i])
		{
			_lastSpeed[i] = abs(voltages[i]);
			motors[i]->setSpeed(_lastSpeed[i]);
		}
	}
}

void Mecanum::set_angle(double angle)
{
	_angle = angle;

	_mag[0] = sin(angle+PI_4);
	_mag[1] = cos(angle+PI_4);
	_mag[2] = _mag[1];
	_mag[3] = _mag[0];
}
