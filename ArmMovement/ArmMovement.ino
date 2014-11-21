#include "ArmControl.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Mecanum.h>
//#include <Adafruit_PWMServoDriver.h>

#define DEBUG
int incomingByte = 0;
ArmControl control;

void setup()
{
	Serial.begin(115200);
	Mecanum mecanum;
	mecanum.begin();
	mecanum.mecRun(0, 0, 0);
	control.begin();
	
	control.Etch.Etch_Play();

	


}

void loop()
{
	/*Arm_Rear_Home_Left();
	Arm_Rear_Flip_To_Right();
	Arm_Rear_Home_Right();*/
	/*Arm_Front_Home_Left();
	Arm_Front_Flip_To_Right();
	Arm_Front_Home_Right();*/
	//control.rearArm(3,1,0,90,90,-90);
    


}
