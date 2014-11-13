// 
// 
// 

#include "LineFollowControl.h"

LineFollowControl::LineFollowControl(Mecanum* mecanum) {

	mecanumControl = mecanum;

	const int NUM_SENSORS = 8;
	const int TIMEOUT = 2000;

	unsigned char frontSensors[] = { 48,47,46,45,44,43,42,41 };
	const int frontEmitter = 40;
	arrays[FRONT] = new QTRSensorsRC(
		frontSensors,
		NUM_SENSORS,
		TIMEOUT,
		frontEmitter
		);

	unsigned char rightSensors[] = { 23, 24, 25, 26, 27, 28, 29, 30 };
	const int rightEmitter = 22;
	arrays[RIGHT] = new QTRSensorsRC(
		rightSensors,
		NUM_SENSORS,
		TIMEOUT,
		rightEmitter
		);

	unsigned char leftSensors[] = { 39, 38, 37, 36, 35, 34, 33, 32 };
	const int leftEmitter = 31;
	arrays[LEFT] = new QTRSensorsRC(
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
			arrays[array]->calibrate();
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

void LineFollowControl::followUntilWhite() {
	int lastError = 0;

	do {
		lastError = update(lastError);
	} while (!allWhite(getCurrentSensor()));

	// Turn off the motors
	mecanumControl->mecRun(0, 0, 0);
}

void LineFollowControl::followUntilLine(int side) {
	const int THRESHOLD = 200;
	const int NUM_SENSORS = 8;
	unsigned int sensors[NUM_SENSORS];
	int lastError = 0;
	int waitPosition = 0;

	do {
		lastError = update(lastError);

		waitPosition = arrays[side]->readLine(sensors, QTR_EMITTERS_ON, 1);
		Serial.println(waitPosition);
	} while (waitPosition > THRESHOLD || waitPosition < -THRESHOLD);

	// Turn off the motors
	mecanumControl->mecRun(0, 0, 0);
}

QTRSensorsRC* LineFollowControl::getCurrentSensor() {
	return arrays[currentSide];
}

QTRSensorsRC* LineFollowControl::getFrontSensor() {
	return arrays[FRONT];
}
QTRSensorsRC* LineFollowControl::getRightSensor() {
	return arrays[RIGHT];
}
QTRSensorsRC* LineFollowControl::getLeftSensor() {
	return arrays[LEFT];
}
QTRSensorsRC* LineFollowControl::getBackSensor() {
	return arrays[BACK];
}

double LineFollowControl::getCurrentAngle() {
	return currentAngle;
}

bool LineFollowControl::allWhite(QTRSensorsRC* sensor) {

	const int NUM_SENSORS = 8;
	const int THRESHOLD = 800;

	unsigned int sensorValues[NUM_SENSORS];

	sensor->readCalibrated(sensorValues);

	for (int i = 0; i < NUM_SENSORS; i++) {
		if (sensorValues[i] > THRESHOLD) {
			return false;
		}
	}

	return true;
}

int LineFollowControl::update(int lastError) {

	const int NUM_SENSORS = 8;

	unsigned int sensors[NUM_SENSORS];
	const int FOLLOWER_OFFSET = 3500;

	// PID constants
	const double Kp = 1.0f / FOLLOWER_OFFSET; // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
	const double Kd = 0.0005f; // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd)

	// Read the line follower
	int position = getCurrentSensor()->readLine(sensors, QTR_EMITTERS_ON, 1);

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
	mecanumControl->mecRun(speed, currentAngle, rotation);

	// Output the values
	Serial.print("Error: ");
	Serial.print(error);
	Serial.print("\tSpeed: ");
	Serial.print(speed);
	Serial.print("\tRotation: ");
	Serial.print(rotation);
	Serial.println();

	return error;
}


void LineFollowControl::followInfinitely()
{
	int lastError = 0;

	// Infinite loop
	while(true) {
		update(lastError);
	}
}


void LineFollowControl::defaultCalibration(void)
{
	// Front
	unsigned int frontCalibratedMax[] = {
		0, 0, 0, 0, 0, 0, 0, 0
	};
	arrays[FRONT]->calibratedMaximumOn = frontCalibratedMax;

	unsigned int frontCalibratedMin[] = {
		0, 0, 0, 0, 0, 0, 0, 0
	};
	arrays[FRONT]->calibratedMinimumOn = frontCalibratedMin;

	// Left
	unsigned int leftCalibratedMax[] = {
		0, 0, 0, 0, 0, 0, 0, 0
	};
	arrays[LEFT]->calibratedMaximumOn = leftCalibratedMax;

	unsigned int leftCalibratedMin[] = {
		0, 0, 0, 0, 0, 0, 0, 0
	};
	arrays[LEFT]->calibratedMinimumOn = leftCalibratedMin;

	// Right
	unsigned int rightCalibratedMax[] = {
		0, 0, 0, 0, 0, 0, 0, 0
	};
	arrays[RIGHT]->calibratedMaximumOn = rightCalibratedMax;

	unsigned int rightCalibratedMin[] = {
		0, 0, 0, 0, 0, 0, 0, 0
	};
	arrays[RIGHT]->calibratedMinimumOn = rightCalibratedMin;
}
