// 
// 
// 

#include "ArmControl.h"

const int ArmControl::Front_Arm[NUM_SERVOS] = { 8, 9, 11, 12, 13, 14 };// skips 12 intentionally
const int ArmControl::Rear_Arm[NUM_SERVOS] = { 0, 1, 2, 3, 4, 5 };

const double ArmControl::A = 4.75;
const double ArmControl::B = 5.00;

const double ArmControl::SPEED = 1.0;

ArmControl::ArmControl() :
	// Initialize classes
	Etch(this), Simon(this), Rubiks(this), Card(this)
{
	// Initialize the PWM controller
	pwm.begin();
	pwm.setPWMFreq(60);
}

void ArmControl::flipFlop()
{
	RearHomeLeft();
	RearFlipToRight();
	RearHomeRight();
	RearFlipToLeft();
	RearHomeLeft();

	frontHomeLeft();
	FrontFlipToRight();
	frontHomeRight();
	FrontFlipToLeft();
	frontHomeLeft();
}


int ArmControl::frontArm(double x, double y, double z, int g, double wr, int wa)
{
	double r = sqrt(x*x + y*y);
	z = z + r*(.5);
	wa=wa+1.5*r;
	double Base_Rotation = degrees(atan2(y, x));
	double M = sqrt((z*z) + (r*r));
	if (M <= 0)
		return 1;
	double A1 = atan(z / r);
	if (r <= 0)
		return 1;
	double A2 = acos((A*A - B*B + M*M) / ((A * 2)*M));
	double Elbow = acos((A*A + B*B - M*M) / ((A * 2)*B));
	double Shoulder = A1 + A2;
	Elbow = degrees(Elbow);
	Shoulder = degrees(Shoulder);
	if ((int)Elbow <= 0 || (int)Shoulder <= 0)
		return 1;
	double Wris = abs(wa - Elbow - Shoulder) - 90;

	// Output the positions
	setPosition(Front_Arm[1], Shoulder);
	setPosition(Front_Arm[2], 180 - Elbow);
	setPosition(Front_Arm[3], 180 - Wris);
	setPosition(Front_Arm[0], Base_Rotation);
	setPosition(Front_Arm[4], wr);
	setPosition(Front_Arm[5], g);

	return 0;
}


void ArmControl::setPosition(int pin, int position)
{
	int pulseLength = map(position, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(pin, 0, pulseLength);
}


int ArmControl::rearArm(double x, double y, double z, int g, double wr, int wa)
{
	double r = sqrt(x*x + y*y);
	z = z + r*(.5);
	wa=wa+3*r;
	double Base_Rotation = degrees(atan2(y, x));
	double M = sqrt((z*z) + (r*r));

	if (M <= 0)
	{
		Serial.print("M");
		return 1;
	}

	double A1 = atan(z / r);
	if (r <= 0)
	{
		Serial.print("r");
		return 1;
	}

	double A2 = acos((A*A - B*B + M*M) / ((A * 2)*M));
	double Elbow = acos((A*A + B*B - M*M) / ((A * 2)*B));
	double Shoulder = A1 + A2;
	Elbow = degrees(Elbow);
	Shoulder = degrees(Shoulder);
	if ((int)Elbow <= 0 || (int)Shoulder <= 0)
	{
		Serial.print("S");
		return 1;
	}

	double Wris = abs(wa - Elbow - Shoulder) - 90;

	// Output the positions
	setPosition(Rear_Arm[1], Shoulder);
	setPosition(Rear_Arm[2], 180 - Elbow);
	setPosition(Rear_Arm[3], 180 - Wris);
	setPosition(Rear_Arm[0], Base_Rotation);
	setPosition(Rear_Arm[4], wr);
	setPosition(Rear_Arm[5], g);

	return 0;
}

void ArmControl::frontHomeRight()
{
	frontArm(-1, 0, 2, 90, 90, -30);
	delay(1500);
}

void ArmControl::frontHomeLeft()
{
	frontArm(-1, 0, 2, 90, 90, -30);
	delay(1500);
}


void ArmControl::FrontFlipToLeft()
{
	frontArm(3, 0, 5, 90, 90, 0);
	delay(1000);

	frontArm(-3, 0, 5, 90, 90, 0);
	delay(1000);
}


void ArmControl::FrontFlipToRight()
{
	frontArm(-3, 0, 5, 90, 90, 0);
	delay(1000);

	frontArm(3, 0, 5, 90, 90, 0);
	delay(1000);
}


void ArmControl::RearHomeLeft()
{
	rearArm(1, 0, 2, 90, 90, -30);
	delay(1500);
}


void ArmControl::RearHomeRight()
{
	rearArm(-1, 0, 2, 90, 90, -30);
	delay(1500);
}


void ArmControl::RearFlipToRight()
{
	rearArm(3, 0, 5, 90, 90, 0);
	delay(1000);

	rearArm(-3, 0, 5, 90, 90, 0);
	delay(1000);
}


void ArmControl::RearFlipToLeft()
{
	rearArm(-3, 0, 5, 90, 90, 0);
	delay(1000);

	rearArm(3, 0, 5, 90, 90, 0);
	delay(1000);
}


void ArmControl::ZeroXY(void)
{
	for (double zaxis = -5; zaxis < 5; zaxis += .1) {
		rearArm(0, 4, zaxis, 90, 90, -90);
		delay(100);
	}
	for (double zaxis = 5; zaxis > -5; zaxis -= .1) {
		rearArm(0, 4, zaxis, 90, 90, -90);
		delay(100);
	}
}


void ArmControl::ZeroYZ(void)
{
	for (double xaxis = 4; xaxis < 10; xaxis += .1) {
		rearArm(xaxis, 4, 0, 90, 90, -75);
		delay(100);
	}
	for (double xaxis = 10; xaxis > 4; xaxis -= .1) {
		rearArm(xaxis, 4, 0, 90, 90, -75);
		delay(100);
	}
}


void ArmControl::ZeroXZ(void)
{
	for (double yaxis = 4; yaxis < 10; yaxis += .1) {
		rearArm(4, yaxis, 0, 90, 90, -75);
		delay(100);
	}
	for (double yaxis = 10; yaxis > 4; yaxis -= .1) {
		rearArm(4, yaxis, 0, 90, 90, -75);
		delay(100);
	}
}
