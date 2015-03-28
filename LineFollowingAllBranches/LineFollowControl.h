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
	LineFollowControl(Mecanum*);

	void calibrate();

	void setSide(int);

	QTRSensorsRC* getCurrentSensor();
	QTRSensorsRC* getFrontSensor();
	QTRSensorsRC* getRightSensor();
	QTRSensorsRC* getLeftSensor();
	QTRSensorsRC* getBackSensor();

	double getCurrentAngle();

	void followUntilWhite();
	void followUntilLine(int);

private:
	// Constant data members
	static const int NUM_ARRAYS = 4;
	static const int NUM_SENSORS = 8;

	// Variable data members
	int currentSide;
	double currentAngle;
	double Kp;
	double Kd;
	double Ki;
	QTRSensorsRC* arrays[NUM_ARRAYS];
	Mecanum* mecanumControl;
	unsigned int sensorValues[NUM_SENSORS];
	bool corner_rotations;
	// Controls how quickly the robot moves forward while navigating the line
	double nav_speed;

	// Functions
	int whiteCount(QTRSensorsRC* array);
	int update(int lastError, int oppositeSensor = -1);
	bool CenterSensor(int sensor);
public:
	void followInfinitely();
	void defaultCalibration(void);
	void RotateUntilLine(double rotation);
	void RotateUntilLine(double rotation, int side);
	void CenterOnLine(int sensor1, int sensor2);
	void set_corner_rotations(bool corner_rotations);
	bool IsExactlyCenteredOnLine(int sensor);
	void DefaultCalibrationOtherSide();
	int SearchForBranch(int sensor1, int sensor2);
	bool IsCenteredOnLine(int sensor, bool offset);
	bool IsCenterOffLine(int sensor);
	void set_speed(double speed);
};

#endif

