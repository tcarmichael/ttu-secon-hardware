// 
// 
// 

#include "LineFollowControl.h"

LineFollowControl::LineFollowControl(Mecanum* mecanum) : fudge_factor(0), sensorValues()
, corner_rotations()
{

	mecanumControl = mecanum;

	const int TIMEOUT = 2000;

	unsigned char frontSensors[] = { 41,42,43,44,45,46,47,48 };
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

		Kp = 3.0 / FOLLOWER_OFFSET;
		Kd = 0.0005;
		fudge_factor = 0.0;
		break;

	case RIGHT:
		currentAngle = PI / 2;

		Kp = 1.0 / FOLLOWER_OFFSET;
		Kd = 0.001;
		fudge_factor = 0.00;
		break;

	case LEFT:
		currentAngle = 3 * PI / 2;

		Kp = 1.0 / FOLLOWER_OFFSET;
		Kd = 0.001;
		fudge_factor = 0.0;
		break;

	case BACK:
		currentAngle = PI;
		break;
	}
}

void LineFollowControl::followUntilWhite() {
	int lastError = 0;

	do {
		lastError = update(lastError);

		// Go a bit past the corners if in corner rotation mode
		if (corner_rotations)
		{
			int position = arrays[currentSide]->readLine(sensorValues, QTR_EMITTERS_ON, 1);

			// Keep going its current speed until it reaches the middle of the line
			if (position == -3500 || position == 3500)
			{
				bool left_center, right_center;
				do
				{
					left_center = IsCenteredOnLine(LEFT);
					right_center = IsCenteredOnLine(RIGHT);
				} while (!left_center && !right_center);

				if (left_center)
				{
					RotateUntilLine(1.0);
				}
				else if (right_center)
				{
					RotateUntilLine(-1.0);
				}
			}
		}
	} while (whiteCount(getCurrentSensor()) < 8);

	// Turn off the motors
	mecanumControl->mecRun(0, 0, 0);
}

void LineFollowControl::followUntilLine(int side) {
	int lastError = 0;

	if (currentSide == RIGHT || currentSide == LEFT) {
		// Follow line until the sensor crosses the line
		do {
			lastError = update(lastError);
		} while (whiteCount(getCurrentSensor()) < 5);
		Serial.println("Crossed line");

		// Stay at the same velocity until the other line sensors detect a line
		do {
			// Beware of magic number
			arrays[side]->read(sensorValues, QTR_EMITTERS_ON);
		} while (sensorValues[3] > 800 || sensorValues[4] > 800);
	}
	else {

		while (!IsCenteredOneLine(side)) {
			lastError = update(lastError)
		}
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
	//rotation = (rotation > 1) ? 1 : rotation;
	//rotation = (rotation < -1) ? -1 : rotation;

	// Calculate the speed
	double speed = 1.0 * (1.0 - abs(error) / ((double)FOLLOWER_OFFSET));
	if (speed < 0) speed = 0;

	// Send the speed
	mecanumControl->mecRun(speed, currentAngle, rotation + fudge_factor);

	// Output the values
	Serial.print("Error: ");
	Serial.print(error);
	//Serial.print("\tSpeed: ");
	//Serial.print(speed);
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
		160, 110, 110, 100, 90, 110, 170, 170
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
		160, 190, 190, 170, 160, 140, 190, 300
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
	RotateUntilLine(rotation, currentSide);
}

void LineFollowControl::RotateUntilLine(double rotation, int side)
{
	mecanumControl->mecRun(0, 0, rotation);

	unsigned int sensors[NUM_SENSORS];

	// Wait for black
	do {
		arrays[side]->read(sensors);
	} while (sensors[3] < 800 || sensors[4] < 800);

	// Wait for white
	do {
		arrays[side]->read(sensors);
	} while (sensors[3] > 800 || sensors[4] > 800);

	mecanumControl->mecRun(0, 0, 0);
}


void LineFollowControl::CenterOnLine(int sensor1, int sensor2)
{
	int position1, position2;

	while (true)
	{
		position1 = arrays[sensor1]->readLine(sensorValues, QTR_EMITTERS_ON, 1);
		position2 = arrays[sensor2]->readLine(sensorValues, QTR_EMITTERS_ON, 1);
		if ( (position1 < 3550 && position1 > 3450) || (position2 < 3550 && position2 > 3450) ) return;

		CenterSensor(sensor1);
		
		position1 = arrays[sensor1]->readLine(sensorValues, QTR_EMITTERS_ON, 1);
		position2 = arrays[sensor2]->readLine(sensorValues, QTR_EMITTERS_ON, 1);
		if ( (position1 < 3550 && position1 > 3450) || (position2 < 3550 && position2 > 3450) ) return;

		CenterSensor(sensor2);
	}
}


bool LineFollowControl::CenterSensor(int sensor)
{
	const int TOLERANCE = 50;
	const int CENTER = 3500;
	const int LEFT = CENTER - TOLERANCE;
	const int RIGHT = CENTER + TOLERANCE;

	int position = arrays[sensor]->readLine(sensorValues, QTR_EMITTERS_ON, 1);

	int direction = 0;

	// Left of line
	if (position < LEFT) {
		direction = -100;
	}
	// Right of line
	else if (position > RIGHT) {
		direction = 100;
	}
	else {
		return false;
	}

	// Move the side
	switch (sensor) {
	case LineFollowControl::LEFT:
		mecanumControl->WriteDirect(direction, 0, direction, 0);
		break;

	case LineFollowControl::RIGHT:
		mecanumControl->WriteDirect(0, -direction, 0, -direction);
		break;
	}

	// Wait until it is centered on the line
	while (position < LEFT || position > RIGHT) {
		position = arrays[sensor]->readLine(sensorValues, QTR_EMITTERS_ON, 1);
	}

	// Stop robot
	mecanumControl->mecRun(0, 0, 0);
	return true;
}


void LineFollowControl::set_corner_rotations(bool new_corner_rotations)
{
	corner_rotations = new_corner_rotations;
}


bool LineFollowControl::IsCenteredOnLine(int sensor)
{
	const int THRESHOLD = 800;

	// Read the raw values from the line sensor
	arrays[sensor]->read(sensorValues);

	// If the middle two sensors detect a line
	return sensorValues[3] < THRESHOLD && sensorValues[4] < THRESHOLD;
}
