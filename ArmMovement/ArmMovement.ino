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

	
}
