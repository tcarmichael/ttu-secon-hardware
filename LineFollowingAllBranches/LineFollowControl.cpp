// 
// 
// 

#include "LineFollowControl.h"

LineFollowControl::LineFollowControl(Mecanum* mecanum) : fudge_factor(0), sensorValues()
, corner_rotations()
{

	mecanumControl = mecanum;

	const int TIMEOUT = 2000;

	unsigned char frontSensors[] = { 22,23,24,25,26,27,28,29 };
	const int frontEmitter = 14;
	arrays[FRONT] = new QTRSensorsRC(
		frontSensors,
		NUM_SENSORS,
		TIMEOUT,
		frontEmitter
		);

	unsigned char rightSensors[] = { 45, 44, 43, 42, 41, 40, 39, 38 };
	const int rightEmitter = 16;
	arrays[RIGHT] = new QTRSensorsRC(
		rightSensors,
		NUM_SENSORS,
		TIMEOUT,
		rightEmitter
		);

	unsigned char leftSensors[] = { 53, 52, 51, 50, 49, 48, 47, 46 };
	const int leftEmitter = 17;
	arrays[LEFT] = new QTRSensorsRC(
		leftSensors,
		NUM_SENSORS,
		TIMEOUT,
		leftEmitter
		);

	/*
	unsigned char BackSensors[] = { 37, 36, 35, 34, 33, 32, 31, 30 };
	const int BackEmitter = 15;
	arrays[BACK] = new QTRSensorsRC(
		BackSensors,
		NUM_SENSORS,
		TIMEOUT,
		BackEmitter
		);
	*/

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

		Kp = 0.35 / FOLLOWER_OFFSET;
		Kd = 0.00000001;
		fudge_factor = 0.0;
		break;

	case RIGHT:
		
		currentAngle = PI / 2;

		Kp = 0.4 / FOLLOWER_OFFSET;
		//Kd = 0.00001;
		Kd = 0;
		fudge_factor = 0.00;
		break;

	case LEFT:
		currentAngle = 3 * PI / 2;

		Kp = 0.3 / FOLLOWER_OFFSET;
		Kd = 0.000001;
		fudge_factor = 0.0;
		break;

	case BACK:
		currentAngle = PI;
		break;
	}
}

void LineFollowControl::followUntilWhite() {
	int lastError = 0;
	bool test = true;
	do {
		lastError = update(lastError);

		// Go a bit past the corners if in corner rotation mode
		if (corner_rotations)
		{
			int position = arrays[currentSide]->readLine(sensorValues, QTR_EMITTERS_ON, 1);

			// Keep going its current speed until it reaches the middle of the line
			if (position == 0 || position == 7000)
			{
				bool left_center, right_center;
				do
				{
					left_center = IsCenteredOnLine(LEFT);
					right_center = IsCenteredOnLine(RIGHT);
				} while (!left_center && !right_center);

				if (left_center)
				{
					Serial.println("Rotating Left");
					RotateUntilLine(1.0);
				}
				else if (right_center)
				{
					Serial.println("Rotating Right");
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
		} while (whiteCount(getCurrentSensor()) < 8);
		Serial.println("Crossed line");

		// Stay at the same velocity until the other line sensors detect a line
		do {
			// Beware of magic number
			arrays[side]->read(sensorValues, QTR_EMITTERS_ON);
		} while (sensorValues[3] > 800 || sensorValues[4] > 800);
	}
	else {

		/*do
		{
			lastError = update(lastError);

			arrays[side]->read(sensorValues, QTR_EMITTERS_ON);
		} while (sensorValues[5] > 800);*/

		while (!IsCenteredOnLine(side)) {
			lastError = update(lastError);
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

int LineFollowControl::update(int lastError, int opposite_sensor) {

	const int FOLLOWER_OFFSET = 3500;

	// Read the line follower
	int position = getCurrentSensor()->readLine(sensorValues, QTR_EMITTERS_ON, 1);

	// Calculate the error
	// Positive error is to the left; negative error is to the right
	int error = position - FOLLOWER_OFFSET;
	Serial.println(error);

	// Convert the error into a motor speed
	double rotation = Kp * error + Kd * (error - lastError);

	// Bounds-checking
	//rotation = (rotation > 1) ? 1 : rotation;
	//rotation = (rotation < -1) ? -1 : rotation;

	// Calculate the speed
	double speed = 0.5 * (1.0 - abs(error) / ((double)FOLLOWER_OFFSET));  // Savannah changed this 0.9
	//double speed = 0.7;
	if (speed < 0) speed = 0;

	// Calculate the opposite angle
	double angle_offset = 0;
	//if (opposite_sensor != -1)
	//{
	//	// Constant Kp
	//	const double opposite_Kp = 0.01 *(PI / 2) / FOLLOWER_OFFSET;

	//	unsigned int other_sensors[NUM_SENSORS];

	//	position = arrays[opposite_sensor]->readLine(other_sensors, QTR_EMITTERS_ON, 1);
	//	error = position - FOLLOWER_OFFSET;

	//	// Put the position into the PID
	//	angle_offset = opposite_Kp * error;
	//}

	// Send the speed
	/*Serial.print("\tSpeed: ");
	Serial.print(speed);*/
	mecanumControl->mecRun(speed, currentAngle - angle_offset, rotation + fudge_factor);

	// Output the values
	for (int i = 0; i < 8; i++)
	{
		Serial.print(sensorValues[i]);
		Serial.print(' ');
	}
	Serial.println();
	/*Serial.print("Error: ");
	Serial.print(error);*/
	/*Serial.print("\tSpeed: ");
	Serial.print(speed);
	Serial.print("\tRotation: ");*/
	//Serial.println(rotation);
	/*Serial.println();*/

	return error;
}


void LineFollowControl::followInfinitely()
{
	int lastError = 0;

	// Infinite loop
	while(true) {
		lastError = update(lastError, LineFollowControl::LEFT);
		// UpdateAngle(LineFollowControl::RIGHT, LineFollowControl::LEFT);
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
		130, 110, 100, 90, 90, 110, 170, 170
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
		130, 150, 150, 140, 150, 130, 150, 240
	};

	// Initialize back
	arrays[BACK]->calibratedMaximumOn = new unsigned int[8];
	arrays[BACK]->calibratedMinimumOn = new unsigned int[8];
	unsigned int backCalibratedMax[] = {
		2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000
	};
	unsigned int backCalibratedMin[] = {
		50, 50, 50, 50, 50, 50, 50, 50
	};

	// Write to the new arrays
	for (int i = 0; i < 8; i++) {
		arrays[FRONT]->calibratedMaximumOn[i] = frontCalibratedMax[i];
		arrays[FRONT]->calibratedMinimumOn[i] = frontCalibratedMin[i];

		arrays[LEFT]->calibratedMaximumOn[i] = leftCalibratedMax[i];
		arrays[LEFT]->calibratedMinimumOn[i] = leftCalibratedMin[i];

		arrays[RIGHT]->calibratedMaximumOn[i] = rightCalibratedMax[i];
		arrays[RIGHT]->calibratedMinimumOn[i] = rightCalibratedMin[i];

		arrays[BACK]->calibratedMaximumOn[i] = backCalibratedMax[i];
		arrays[BACK]->calibratedMinimumOn[i] = backCalibratedMin[i];
	}
}

void LineFollowControl::RotateUntilLine(double rotation)
{
	RotateUntilLine(rotation, currentSide);
}

void LineFollowControl::RotateUntilLine(double rotation, int side)
{
	mecanumControl->mecRun(0, 0, rotation);

	// Wait for sensor to leave the current line
	while (!IsCenterOffLine(side));

	// Wait for sensor to detect the new line
	while (!IsCenteredOnLine(side));

	mecanumControl->mecRun(0, 0, 0);
}


void LineFollowControl::CenterOnLine(int sensor1, int sensor2)
{
	int position1, position2;
	const unsigned long TIMEOUT = 5e3; // 5 seconds
	unsigned long start = millis();
	while (millis() - start < TIMEOUT)
	{
		position1 = arrays[sensor1]->readLine(sensorValues, QTR_EMITTERS_ON, 1);
		position2 = arrays[sensor2]->readLine(sensorValues, QTR_EMITTERS_ON, 1);
		if ( (position1 < 3600 && position1 > 3400) && (position2 < 3600 && position2 > 3400) ) return;
		Serial.print(position1);
		Serial.print(' ');
		Serial.print(position2);
		Serial.println();

		CenterSensor(sensor1);
		delay(100);
		
		position1 = arrays[sensor1]->readLine(sensorValues, QTR_EMITTERS_ON, 1);
		position2 = arrays[sensor2]->readLine(sensorValues, QTR_EMITTERS_ON, 1);
		if ((position1 < 3600 && position1 > 3400) && (position2 < 3600 && position2 > 3400)) return;
		Serial.print(position1);
		Serial.print(' ');
		Serial.print(position2);
		Serial.println();

		CenterSensor(sensor2);
		delay(100);
		
		

	}
}


bool LineFollowControl::CenterSensor(int sensor)
{
	const int TOLERANCE = 100;
	const int CENTER = 3500;
	const int LEFT = CENTER - TOLERANCE;
	const int RIGHT = CENTER + TOLERANCE;

	int position = arrays[sensor]->readLine(sensorValues, QTR_EMITTERS_ON, 1);

	int direction = 0;

	// Left of line
	if (position < LEFT) {
		direction = -65;
	}
	// Right of line
	else if (position > RIGHT) {
		direction = 65;
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


bool LineFollowControl::IsExactlyCenteredOnLine(int sensor)
{
	const int CENTER = 3500; 
	const int THRESHOLD = 50;
	const int LEFT = CENTER - THRESHOLD;
	const int RIGHT = CENTER + THRESHOLD;
	int position = arrays[sensor]->readLine(sensorValues, QTR_EMITTERS_ON, 1);

	return position < RIGHT && position > LEFT && sensorValues[3] < 400 && sensorValues [4] < 400;
}


void LineFollowControl::DefaultCalibrationOtherSide()
{
	// Initialize front
	arrays[FRONT]->calibratedMaximumOn = new unsigned int[8];
	arrays[FRONT]->calibratedMinimumOn = new unsigned int[8];
	unsigned int frontCalibratedMax[] = {
		2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000
	};
	unsigned int frontCalibratedMin[] = {
		90, 100, 60, 60, 100, 110, 150, 160
	};

	// Initialize left
	arrays[LEFT]->calibratedMinimumOn = new unsigned int[8];
	arrays[LEFT]->calibratedMaximumOn = new unsigned int[8];
	unsigned int leftCalibratedMin[] = {
		80, 80, 40, 40, 40, 80, 80, 100
	};
	unsigned int leftCalibratedMax[] = {
		1800, 1300, 1200, 1100, 1000, 1300, 1400, 1500
	};

	// Initialize right
	arrays[RIGHT]->calibratedMaximumOn = new unsigned int[8];
	arrays[RIGHT]->calibratedMinimumOn = new unsigned int[8];
	unsigned int rightCalibratedMax[] = {
		2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000
	};
	unsigned int rightCalibratedMin[] = {
		90, 100, 100, 90, 100, 80, 90, 140
	};

	// Initialize back
	arrays[BACK]->calibratedMaximumOn = new unsigned int[8];
	arrays[BACK]->calibratedMinimumOn = new unsigned int[8];
	unsigned int backCalibratedMax[] = {
		2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000
	};
	unsigned int backCalibratedMin[] = {
		50, 50, 50, 50, 50, 50, 50, 50
	};



	// Write to the new arrays
	for (int i = 0; i < 8; i++) {
		arrays[FRONT]->calibratedMaximumOn[i] = frontCalibratedMax[i];
		arrays[FRONT]->calibratedMinimumOn[i] = frontCalibratedMin[i];

		arrays[LEFT]->calibratedMaximumOn[i] = leftCalibratedMax[i];
		arrays[LEFT]->calibratedMinimumOn[i] = leftCalibratedMin[i];

		arrays[RIGHT]->calibratedMaximumOn[i] = rightCalibratedMax[i];
		arrays[RIGHT]->calibratedMinimumOn[i] = rightCalibratedMin[i];

		arrays[BACK]->calibratedMaximumOn[i] = backCalibratedMax[i];
		arrays[BACK]->calibratedMinimumOn[i] = backCalibratedMin[i];
	}
}


void LineFollowControl::UpdateAngle(int front_sensor, int back_sensor)
{
	const double Kp = 1.0;

	int front_distance = arrays[front_sensor]->readLine(sensorValues, QTR_EMITTERS_ON, 1);
	int back_distance = arrays[front_sensor]->readLine(sensorValues, QTR_EMITTERS_ON, 1);

	double angle = CalculateAngle(front_distance, back_distance);

	double error = Kp * angle;

	double speed = 1.0 * (1.0 - abs(angle) / (PI / 2));

	// Write to the motors
	mecanumControl->mecRun(speed, currentAngle, error);
}


double LineFollowControl::CalculateAngle(int front_distance, int back_distance)
{
	// 0.0010714 cm/unit
	front_distance *= 0.0010714;
	back_distance *= 0.0010714;

	double Theta = 0;

	if (front_distance / front_distance == back_distance / back_distance)
	{
		Theta = (PI / 2) - atan2(7.5, (front_distance + back_distance));
	}
	else
	{
		Theta = (PI / 2) - atan2(7.5, (front_distance - back_distance));
	}

	return Theta;
}


bool LineFollowControl::IsCenterOffLine(int sensor)
{
	const int THRESHOLD = 800;

	// Read the raw values from the line sensor
	arrays[sensor]->read(sensorValues);

	// If the middle two sensors detect a line
	return !(sensorValues[3] < THRESHOLD || sensorValues[4] < THRESHOLD);
}
