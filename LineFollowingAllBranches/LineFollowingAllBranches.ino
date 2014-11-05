#include <Mecanum.h>

#include <Wire.h>

#include <QTRSensors.h>
#include <Adafruit_MotorShield.h>

#include "LineFollowControl.h"

const int FOLLOWER_OFFSET = 3500;

// PID constants
const double Kp = 1.0f / FOLLOWER_OFFSET; // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
const double Kd = 0.0005f; // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd)

const int NUM_SENSORS = 8;

LineFollowControl lineFollowerControl;

// Interacts with the mecanum wheels and the motor shield
Mecanum mecanum;

bool allWhite(QTRSensorsRC sensor) {

	const int THRESHOLD = 800;
	
	unsigned int sensorValues[NUM_SENSORS];
	
	sensor.readCalibrated(sensorValues);
	
	for (int i = 0; i < NUM_SENSORS; i++) {
		if (sensorValues[i] < THRESHOLD) {
			return false;
		}
	}
	
	return true;
}

void setup() {
	Serial.begin(9600);
	Serial.println("Starting calibration");

	// Calibrate the line-following sensor
	delay(500);
	
	mecanum.begin();
	
	followLine();
}

void followLine() {
	int lastError = 0;
	unsigned int sensors[NUM_SENSORS];
	
	do {
		// Read the line follower
		int position = lineFollowerControl.getCurrentSensor().readLine(sensors, QTR_EMITTERS_ON, 1);

		// Calculate the error
		// Positive error is to the left; negative error is to the right
		int error = position - FOLLOWER_OFFSET;

		// Convert the error into a motor speed
		double rotation = Kp * error + Kd * (error - lastError);

		lastError = error;

		// Bounds-checking
		rotation = (rotation > 1) ? 1 : rotation;
		rotation = (rotation < -1) ? -1 : rotation;

		// Calculate the speed
		double speed = 0.6 * (1.0-abs(error)/((double) FOLLOWER_OFFSET));
		speed = (speed > 1) ? 1 : speed;
		speed = (speed < 0) ? 0 : speed;
		
		// Send the speed
		mecanum.mecRun(speed, 0, rotation);
	} while (!allWhite(lineFollowerControl.getLeftSensor()));
	
}

void loop() {
	// Empty
}
