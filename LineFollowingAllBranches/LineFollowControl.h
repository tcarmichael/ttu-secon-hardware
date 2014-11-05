#ifndef LineFollowControl_h
#define LineFollowControl_h

#include "QTRSensors.h"

const int FRONT = 0;
const int RIGHT = 1;
const int LEFT = 2;
const int BACK = 3;

const int NUM_ARRAYS = 4;

class LineFollowControl {
public:
	LineFollowControl();

	void setSide(int);
	
	QTRSensorsRC getCurrentSensor();
	QTRSensorsRC getFrontSensor();
	QTRSensorsRC getRightSensor();
	QTRSensorsRC getLeftSensor();
	QTRSensorsRC getBackSensor();
	
	double getCurrentAngle();
	
private:
	int currentSide;
	double currentAngle;
	QTRSensorsRC arrays[NUM_ARRAYS];
};

// LineFollowControl.h
#endif