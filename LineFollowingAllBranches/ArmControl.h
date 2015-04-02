// ArmControl.h

#ifndef _ARMCONTROL_h
#define _ARMCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

//#include "Adafruit_PWMServoDriver.h"
#include <Adafruit_MotorShield.h>
#include "GameControl.h"
#include "EtchControl.h"
#include "SimonControl.h"
#include "RubiksControl.h"
#include "CardControl.h"

class ArmControl
{
	friend class EtchControl;
	friend class SimonControl;
	friend class RubiksControl;
	friend class CardControl;

private:


	const static int SERVOMIN = 150; // This is the 'minimum' pulse length count (out of 4096)
	const static int SERVOMAX = 650; // This is the 'maximum' pulse length count (out of 4096)

	const static int NUM_SERVOS = 6;
	const static int Front_Arm[NUM_SERVOS];
	const static int Rear_Arm[NUM_SERVOS];

	const static double A ;
	const static double B;

	// Arm speed variables
	const static double SPEED;
	const static int SPS = 3;
	const static double GripConstant = 100;

	Adafruit_PWMServoDriver pwm;

public:
	ArmControl();

	EtchControl Etch;
	SimonControl Simon;
	RubiksControl Rubiks;
	CardControl Card;
	double newWR = -10;

	void begin();
	void flipFlop(void);
	int frontArm(double x, double y, double z, int g, double wr, int wa);
	int rearArm(double x, double y, double z, int g, double wr, int wa);
	void setPosition(int pin, int position);

	void frontHomeRight();
	void frontHomeLeft();
	void FrontFlipToLeft();
	void FrontFlipToRight();
	void RearHomeLeft();
	void RearHomeRight();
	void RearFlipToRight();
	void RearFlipToLeft();
	void ZeroXY();
	void ZeroYZ();
	void ZeroXZ();
	void Rear_Smooth_Move(double x1, double y1, double z1, int g1, double wr1, int wa1, double x2, double y2, double z2, int g2, double wr2, int wa2, double time);
	void Front_Smooth_Move(double x1, double y1, double z1, int g1, double wr1, int wa1, double x2, double y2, double z2, int g2, double wr2, int wa2, double time);
	void Both_Smooth_Move(double RearCurrent[6],double RearNext[6],double FrontCurrent[6],double FrontNext[6],  double time);
};

#endif
