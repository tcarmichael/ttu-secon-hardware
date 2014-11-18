// 
// 
// 

#include "ArmControl.h"

const int ArmControl::Front_Arm[NUM_SERVOS] = { 8, 9, 11, 12, 13, 14 };// skips 10 intentionally
const int ArmControl::Rear_Arm[NUM_SERVOS] = { 0, 1, 2, 3, 4, 5 };

const double ArmControl::A = 4.75;
const double ArmControl::B = 5.00;

const double ArmControl::SPEED = 1.0;

ArmControl::ArmControl() :
	// Initialize classes
	Etch(this), Simon(this), Rubiks(this), Card(this)
{
}

void ArmControl::begin() {
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
	frontArm(1, 0, 2, 90, 90, -30);
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



void ArmControl::Rear_Smooth_Move(double x1, double y1, double z1, int g1, double wr1, int wa1, double x2, double y2, double z2, int g2, double wr2, int wa2, double time)
{
	double x_inc;
	double y_inc;
	double z_inc;
	double g_inc;
	double wr_inc;
	double wa_inc;
	int I = time / .01;
	x_inc = abs((abs(x2) - abs(x1))) / I;
	y_inc = abs((abs(y2) - abs(y1))) / I;
	z_inc = abs((abs(z2) - abs(z1))) / I;
	g_inc = abs((abs(g2) - abs(g1))) / I;
	wr_inc = abs((abs(wr2) - abs(wr1))) / I;
	wa_inc = abs((abs(wa2) - abs(wa1))) / I;
	double w = 40 / 200;
	Serial.print(g2);
	Serial.print("     ");
	Serial.print(g1);
	Serial.print("     ");
	Serial.print(abs((abs(g2) - abs(g1))));
	Serial.print("     ");
	Serial.print(I);
	Serial.print("     ");
	Serial.print(abs((abs(g2) - abs(g1)))/I);
	Serial.print("     ");
	Serial.print(w);
	Serial.print("\n \n");

	double x_array[I + 1];
	double y_array[I + 1];
	double z_array[I + 1];
	double g_array[I + 1];
	double wr_array[I + 1];
	double wa_array[I + 1];

	x_array[0] = x1;
	for (int temp = 1; temp <= I + 1; temp += 1)
	{
		if (x1 >= x2)
		{
			
			x_array[temp] = x_array[temp - 1] - x_inc;
		}
		if (x2>x1)
		{
			
			x_array[temp] = x_array[temp - 1] + x_inc;
		}
	}


	y_array[0] = y1;
	for (int temp = 1; temp <= I + 1; temp += 1)
	{
		if (y1 >= y2)
		{
			y_array[temp] = y_array[temp - 1] - y_inc;
		}
		if (y2>y1)
		{
			y_array[temp] = y_array[temp - 1] + y_inc;
		}
	}




	z_array[0] = z1;
	for (int temp = 1; temp <= I + 1; temp += 1)
	{
		if (z1 >= z2)
		{
			z_array[temp] = z_array[temp - 1] - z_inc;
		}
		if (z2>z1)
		{
			z_array[temp] = z_array[temp - 1] + z_inc;
		}
	}


	g_array[0] = g1;
	for (int temp = 1; temp <= I + 1; temp += 1)
	{
		if (g1 >= g2)
		{
			g_array[temp] = g_array[temp - 1] - g_inc;
		}
		if (g2>g1)
		{
			g_array[temp] = g_array[temp - 1] + g_inc;
		}
	}





	wa_array[0] = wa1;
	for (int temp = 1; temp <= I + 1; temp += 1)
	{
		if (wa1 >= wa2)
		{
			wa_array[temp] = wa_array[temp - 1] - wa_inc;
		}
		if (wa2>wa1)
		{
			wa_array[temp] = wa_array[temp - 1] + wa_inc;
		}
	}


	wr_array[0] = wr1;
	for (int temp = 1; temp <= I + 1; temp += 1)
	{
		if (wr1 >= wr2)
		{
			wr_array[temp] = wr_array[temp - 1] - wr_inc;
		}
		if (wr2>wr1)
		{
			wr_array[temp] = wr_array[temp - 1] + wr_inc;
		}
	}


	for (int tempWrite = 0; tempWrite <= I + 1; tempWrite += 1)
	{
		rearArm(x_array[tempWrite], y_array[tempWrite], z_array[tempWrite], g_array[tempWrite], wr_array[tempWrite], wa_array[tempWrite]);
		
		delay(10);
	}
}
