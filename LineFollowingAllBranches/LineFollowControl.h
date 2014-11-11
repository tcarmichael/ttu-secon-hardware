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
	// Constant data members
	static const int FRONT = 0;
	static const int RIGHT = 1;
	static const int LEFT = 2;
	static const int BACK = 3;

	// Functions
	LineFollowControl(Mecanum);

	void calibrate();

	void setSide(int);

	QTRSensorsRC getCurrentSensor();
	QTRSensorsRC getFrontSensor();
	QTRSensorsRC getRightSensor();
	QTRSensorsRC getLeftSensor();
	QTRSensorsRC getBackSensor();

	double getCurrentAngle();

	void followUntilWhite();
	void followUntilLine(QTRSensorsRC wait);

private:
	// Constant data members
	static const int NUM_ARRAYS = 4;

	// Variable data members
	int currentSide;
	double currentAngle;
	QTRSensorsRC arrays[NUM_ARRAYS];
	Mecanum mecanumControl;

	// Functions
	bool allWhite(QTRSensorsRC array);
	int update(QTRSensorsRC array, int lastError);
};

#endif

