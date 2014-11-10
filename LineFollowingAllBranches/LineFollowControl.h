// LineFollowControl.h

#ifndef _LINEFOLLOWCONTROL_h
#define _LINEFOLLOWCONTROL_h

// Include libraries
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "QTRSensors.h"
#include "Mecanum.h"

class LineFollowControl
{

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
	// Data members
	static const int NUM_ARRAYS = 4;
	static const int FRONT = 0;
	static const int RIGHT = 1;
	static const int LEFT = 2;
	static const int BACK = 3;

	// Variable data members
	int currentSide;
	double currentAngle;
	QTRSensorsRC arrays[NUM_ARRAYS];

	// Functions
	bool allWhite(QTRSensorsRC array);
	int update(QTRSensorsRC array, Mecanum mecanum, int lastError);
};

#endif

