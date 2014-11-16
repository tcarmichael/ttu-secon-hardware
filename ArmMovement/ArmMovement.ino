#include "ArmControl.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Mecanum.h>
#include <Adafruit_PWMServoDriver.h>

#define DEBUG

ArmControl control;

void setup()
{
	Serial.begin(115200);

	Mecanum mecanum;
	mecanum.begin();
	mecanum.mecRun(0, 0, 0);
	delay(1500);
}

void loop()
{
	/*Arm_Rear_Home_Left();
	Arm_Rear_Flip_To_Right();
	Arm_Rear_Home_Right();

	Arm_Front_Home_Left();
	Arm_Front_Flip_To_Right();
	Arm_Front_Home_Right();*/

	control.rearArm(-8, 2, 0, 90, 90, -90);
	delay(1500);

	control.rearArm(-8.5, 2, -3, 90, 90, -90);
	delay(1500);

	for (double i = 0; i < 4; i = +.1) {
		control.rearArm(-8.5+i, 2, -3, 90, 90, -90);
		delay(100);
	}
}
/* I'm not sure how these functions are different from the other functions
void Arm_Front_Home()
{
}

void Arm_Rear_Home()
{
	Rear_Arm_IK(3, 0, 3, 90, 90, -90);
}*/
