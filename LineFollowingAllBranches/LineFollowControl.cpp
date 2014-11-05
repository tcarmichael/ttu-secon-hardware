#include "LineFollowControl.h"
#include "Mecanum.h"

LineFollowControl::LineFollowControl() {

	const int NUM_SENSORS = 8;
	const int TIMEOUT = 2000;

	unsigned char frontSensors[] = {41,42,43,44,45,46,47,48};
	arrays[FRONT] = QTRSensorsRC(
		frontSensors,
		NUM_SENSORS,
		TIMEOUT,
		40
	);
	unsigned char rightSensors[] = {23,24,25,26,27,28,29,30};
	arrays[RIGHT] = QTRSensorsRC(
		rightSensors,
		NUM_SENSORS,
		TIMEOUT,
		22
	);
	unsigned char leftSensors[] = {39,38,37,36,35,34,33,32};
	arrays[LEFT] = QTRSensorsRC(
		leftSensors,
		NUM_SENSORS,
		TIMEOUT,
		31
	);
	/*arrays[BACK] = QTRSensorsRC(
		(unsigned char[]) {41,42,43,44,45,46,47,48},
		NUM_SENSORS,
		TIMEOUT,
		40
	);*/
	
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
		currentAngle = PI_4*2;
		break;
		
	case LEFT:
		currentAngle = PI_4*6;
		break;
		
	case BACK:
		currentAngle = PI_4*4;
		break;
	}
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
