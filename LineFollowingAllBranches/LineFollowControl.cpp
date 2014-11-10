// 
// 
// 

#include "LineFollowControl.h"

LineFollowControl::LineFollowControl() {

	const int NUM_SENSORS = 8;
	const int TIMEOUT = 2000;

	unsigned char frontSensors[] = { 41, 42, 43, 44, 45, 46, 47, 48 };
	const int frontEmitter = 40;
	arrays[FRONT] = QTRSensorsRC(
		frontSensors,
		NUM_SENSORS,
		TIMEOUT,
		frontEmitter
		);

	unsigned char rightSensors[] = { 23, 24, 25, 26, 27, 28, 29, 30 };
	const int rightEmitter = 22;
	arrays[RIGHT] = QTRSensorsRC(
		rightSensors,
		NUM_SENSORS,
		TIMEOUT,
		rightEmitter
		);

	unsigned char leftSensors[] = { 39, 38, 37, 36, 35, 34, 33, 32 };
	const int leftEmitter = 31;
	arrays[LEFT] = QTRSensorsRC(
		leftSensors,
		NUM_SENSORS,
		TIMEOUT,
		leftEmitter
		);

	/*arrays[BACK] = QTRSensorsRC(
	(unsigned char[]) {41,42,43,44,45,46,47,48},
	NUM_SENSORS,
	TIMEOUT,
	40
	);*/

}

void LineFollowControl::calibrate() {

	// Calibrate the line sensors
	for (int i = 0; i < 400; i++) {
		for (int array = 0; array < NUM_ARRAYS - 1; array++) {
			arrays[array].calibrate();
		}
	}
}

void LineFollowControl::setSide(int side) {
	currentSide = side;

	switch (side) {
	case FRONT:
		currentAngle = 0;
		break;

	case RIGHT:
		currentAngle = PI_4 * 2;
		break;

	case LEFT:
		currentAngle = PI_4 * 6;
		break;

	case BACK:
		currentAngle = PI_4 * 4;
		break;
	}
}

void LineFollowControl::followUntilWhite(QTRSensorsRC follow, Mecanum mecanum) {
	int lastError = 0;

	do {
		lastError = update(follow, mecanum, lastError);
	} while (!allWhite(follow));
}

void LineFollowControl::followUntilLine(QTRSensorsRC follow, Mecanum mecanum, QTRSensorsRC wait) {
	const int NUM_SENSORS = 8;
	unsigned int sensors[NUM_SENSORS];
	int lastError = 0;
	int waitPosition = 0;

	do {
		lastError = update(follow, mecanum, lastError);

		waitPosition = wait.readLine(sensors, QTR_EMITTERS_ON, 1);
	} while (waitPosition > 50 || waitPosition < -50);
}

QTRSensorsRC LineFollowControl::getCurrentSensor() {
	return arrays[currentSide];
}

QTRSensorsRC LineFollowControl::getFrontSensor() {
	return arrays[FRONT];
}
QTRSensorsRC LineFollowControl::getRightSensor() {
	return arrays[RIGHT];
}
QTRSensorsRC LineFollowControl::getLeftSensor() {
	return arrays[LEFT];
}

QTRSensorsRC LineFollowControl::getBackSensor() {
	return arrays[BACK];

}

double LineFollowControl::getCurrentAngle() {
	return currentAngle;
}

bool LineFollowControl::allWhite(QTRSensorsRC sensor) {

	const int NUM_SENSORS = 8;
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

int LineFollowControl::update(QTRSensorsRC array, Mecanum mecanum, int lastError) {

	const int NUM_SENSORS = 8;

	unsigned int sensors[NUM_SENSORS];
	const int FOLLOWER_OFFSET = 3500;

	// PID constants
	const double Kp = 1.0f / FOLLOWER_OFFSET; // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
	const double Kd = 0.0005f; // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd)

	// Read the line follower
	int position = array.readLine(sensors, QTR_EMITTERS_ON, 1);

	// Calculate the error
	// Positive error is to the left; negative error is to the right
	int error = position - FOLLOWER_OFFSET;

	// Convert the error into a motor speed
	double rotation = Kp * error + Kd * (error - lastError);

	// Bounds-checking
	rotation = (rotation > 1) ? 1 : rotation;
	rotation = (rotation < -1) ? -1 : rotation;

	// Calculate the speed
	double speed = 0.6 * (1.0 - abs(error) / ((double)FOLLOWER_OFFSET));
	speed = (speed > 1) ? 1 : speed;
	speed = (speed < 0) ? 0 : speed;

	// Send the speed
	mecanum.mecRun(speed, 0, rotation);

	// Output the values
	Serial.print("Error: ");
	Serial.println(error);

	return error;
}
