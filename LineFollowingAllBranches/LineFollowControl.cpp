// 
// 
// 

#include "LineFollowControl.h"

LineFollowControl::LineFollowControl(Mecanum* mecanum) : fudge_factor(0)
{

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

	unsigned char rightSensors[] = { 30, 29, 28, 27, 26, 25, 24, 23 };
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
	const double FOLLOWER_OFFSET = 3500.0;

	switch (side) {
	case FRONT:
		currentAngle = 0;

		Kp = 1.0 / FOLLOWER_OFFSET;
		Kd = 0.0001;
		fudge_factor = 0.0;
		//Kd = 0.0005;
		break;

	case RIGHT:
		currentAngle = PI_4 * 2;

		Kp = 1.0 / FOLLOWER_OFFSET;
		//Kp = 0;
		Kd = 0.001;
		fudge_factor = 0.00;
		//Kd = 0.001;
		//Kd = 0.006;
		break;

	case LEFT:
		currentAngle = PI_4 * 6;

		Kp = 1.0 / FOLLOWER_OFFSET;
		//Kp = 0.0;
		Kd = 0.001;
		fudge_factor = 0.0;
		//Kd = 0.001;
		//Kd = 0.006;
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
	} while (whiteCount(getCurrentSensor()) <= 7);

	// Turn off the motors
	mecanumControl->mecRun(0, 0, 0);
}

void LineFollowControl::followUntilLine(int side) {
	int lastError = 0;
	const int NUM_SENSORS = 8;
	unsigned int sensors[NUM_SENSORS];

	if (currentSide == RIGHT || currentSide == LEFT) {
		// Follow line until the sensor crosses the line
		do {
			lastError = update(lastError);
		} while (whiteCount(getCurrentSensor()) < 5);
		Serial.println("Crossed line");

		// Stay at the same velocity until the other line sensors detect a line
		do {
			// Beware of magic number
			arrays[side]->read(sensors, QTR_EMITTERS_ON);
		} while (sensors[3] > 800 || sensors[4] > 800);
	}
	else {

		do {
			lastError = update(lastError);

			// Beware of magic number
			arrays[side]->read(sensors, QTR_EMITTERS_ON);
		} while (sensors[3] > 800 || sensors[4] > 800);
	}

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

int LineFollowControl::whiteCount(QTRSensorsRC* sensor) {

	const int NUM_SENSORS = 8;
	const int THRESHOLD = 400;
	int whiteCount = 0;

	unsigned int sensorValues[NUM_SENSORS];

	sensor->readCalibrated(sensorValues);

	for (int i = 0; i < NUM_SENSORS; i++) {

		if (sensorValues[i] < THRESHOLD) {
			whiteCount++;
		}
	}

	if (whiteCount == 8) {
		for (int i = 0; i < NUM_SENSORS; i++) {
			Serial.print(sensorValues[i]);
			Serial.print(' ');
		}
		Serial.println();
	}

	return whiteCount;
}

int LineFollowControl::update(int lastError) {
	const int NUM_SENSORS = 8;

	unsigned int sensors[NUM_SENSORS];
	const int FOLLOWER_OFFSET = 3500;

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
	double speed = 1.5 * (1.0 - abs(error) / ((double)FOLLOWER_OFFSET));
	//speed = (speed > 1) ? 1 : speed;
	speed = (speed < 0) ? 0 : speed;

	// Send the speed
	mecanumControl->mecRun(speed, currentAngle, rotation + fudge_factor);

	/*if (error == FOLLOWER_OFFSET || error == -FOLLOWER_OFFSET) {
		mecanumControl->mecRun(0, currentAngle, rotation);
	}
	else {
		mecanumControl->mecRun(0.6, currentAngle, rotation);
	}*/
	/*for (int i = 0; i < 8; i++) {
		Serial.print(sensors[i]);
		Serial.print(' ');
	}*/

	// Output the values
	Serial.print("Error: ");
	Serial.print(error);
	//Serial.print("\tSpeed: ");
	//Serial.print(speed);
	Serial.print("\tRotation: ");
	Serial.print(rotation);
	Serial.println();

	/*if (currentSide == RIGHT || currentSide == LEFT)
	{
		if (error <= -2000 || error >= 2000)
		{
			do {
				arrays[currentSide]->read(sensors);
			} while (sensors[3] > 800 || sensors[4] > 800);
		}
	}*/

	return error;
}


void LineFollowControl::followInfinitely()
{
	int lastError = 0;

	// Infinite loop
	while(true) {
		lastError = update(lastError);
	}
}


void LineFollowControl::defaultCalibration(void)
{
	// Initialize front
	arrays[FRONT]->calibratedMaximumOn = new unsigned int[8];
	arrays[FRONT]->calibratedMinimumOn = new unsigned int[8];
	unsigned int frontCalibratedMax[] = {
		2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000
	};
	unsigned int frontCalibratedMin[] = {
		160, 110, 110, 125, 90, 110, 170, 170
	};

	// Initialize left
	arrays[LEFT]->calibratedMinimumOn = new unsigned int[8];
	arrays[LEFT]->calibratedMaximumOn = new unsigned int[8];
	unsigned int leftCalibratedMin[] = {
		120, 130, 79, 60, 60, 100, 100, 120
	};
	unsigned int leftCalibratedMax[] = {
		2000, 1300, 1200, 1100, 1000, 1300, 1400, 1500
	};

	// Initialize right
	arrays[RIGHT]->calibratedMaximumOn = new unsigned int[8];
	arrays[RIGHT]->calibratedMinimumOn = new unsigned int[8];
	unsigned int rightCalibratedMax[] = {
		2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000
	};
	unsigned int rightCalibratedMin[] = {
		200, 200, 192, 192, 218, 192, 205, 346
	};

	// Write to the new arrays
	for (int i = 0; i < 8; i++) {
		arrays[FRONT]->calibratedMaximumOn[i] = frontCalibratedMax[i];
		arrays[FRONT]->calibratedMinimumOn[i] = frontCalibratedMin[i];

		arrays[LEFT]->calibratedMaximumOn[i] = leftCalibratedMax[i];
		arrays[LEFT]->calibratedMinimumOn[i] = leftCalibratedMin[i];

		arrays[RIGHT]->calibratedMaximumOn[i] = rightCalibratedMax[i];
		arrays[RIGHT]->calibratedMinimumOn[i] = rightCalibratedMin[i];
	}
}


void LineFollowControl::RotateUntilLine(double rotation)
{
	mecanumControl->mecRun(0, 0, rotation);

	const int NUM_SENSORS = 8;
	unsigned int sensors[NUM_SENSORS];

	do {
		arrays[currentSide]->read(sensors);
	} while (sensors[3] > 800 || sensors[4] > 800);

	mecanumControl->mecRun(0, 0, 0);
}
