#ifndef LineFollowControl_h
#define LineFollowControl_h

#include "QTRSensors.h"
#include "Mecanum.h"

class LineFollowControl {
public:
	LineFollowControl();
	
	void calibrate();

	void setSide(int);
	
	QTRSensorsRC getCurrentSensor();
	QTRSensorsRC getFrontSensor();
	QTRSensorsRC getRightSensor();
	QTRSensorsRC getLeftSensor();
	QTRSensorsRC getBackSensor();
	
	double getCurrentAngle();
	
	void followUntilWhite(QTRSensorsRC follow, Mecanum mecanum);
	void followUntilLine(QTRSensorsRC follow, Mecanum mecanum, QTRSensorsRC wait);
	
private:

	const int FRONT = 0;
	const int RIGHT = 1;
	const int LEFT = 2;
	const int BACK = 3;

	const int NUM_ARRAYS = 4;
	
	int currentSide;
	double currentAngle;
	QTRSensorsRC arrays[NUM_ARRAYS];
	
	bool allWhite(QTRSensorsRC array);
	
	int update(QTRSensorsRC array, Mecanum mecanum, int lastError);
};

// LineFollowControl.h
#endif