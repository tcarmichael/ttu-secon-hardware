#include "ArmControl.h"
#include "Arduino.h"

void EtchControl::Etch_Play()
{
	// assumes the knobs have already been grasped with the
	// front arm rotated with the servo box away from the rear arm
	letterI();
	makeSpace();
	letterE();
	makeSpace();
	letterE();
	makeSpace();
	letterE();
}

void EtchControl::makeSpace()
{
	// new letter
	delay(3000);

	// Release knob
	parent->setPosition(parent->Rear_Arm[5], 60);
	delay(500);

	// Rotate wrist
	parent->setPosition(parent->Rear_Arm[4], 175);
	delay(500);

	// Grab knob
	parent->setPosition(parent->Rear_Arm[5], 80);
	delay(500);

	// Scroll over
	parent->setPosition(parent->Rear_Arm[4], 14);
	delay(500);

	// Release knob
	parent->setPosition(parent->Rear_Arm[5], 60);
	delay(500);

	// Rotate wrist
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(500);

	// Grab knob
	parent->setPosition(parent->Rear_Arm[5], 80);
	delay(500);
}

void EtchControl::letterI()
{
	// draw I
	parent->setPosition(parent->Rear_Arm[4], 30);
	delay(500);

	parent->setPosition(parent->Rear_Arm[4], 115);
	delay(500);

	down();
	delay(500);

	parent->setPosition(parent->Rear_Arm[4], 170);
	delay(500);

	parent->setPosition(parent->Rear_Arm[4], 30);
}

void EtchControl::letterE()
{
	int pulselen;
	//draw E
	for (int i = 0; i < 2; i++)
	{
		 // Horizontal forward
		parent->setPosition(parent->Rear_Arm[4], 40);
		delay(500);

		// Horizontal back
		parent->setPosition(parent->Rear_Arm[4], 180);
		down();
	}

	parent->setPosition(parent->Rear_Arm[4], 40);
}

void EtchControl::down()
{
	// Vertical line
	delay(1000);

	// Release knob
	parent->setPosition(parent->Front_Arm[5], 50);
	delay(500);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], 175);
	delay(500);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], 65);
	delay(500);

	// Scroll over
	parent->setPosition(parent->Front_Arm[4], 60);
	delay(500);

	// Release knob
	parent->setPosition(parent->Front_Arm[5], 50);
	delay(500);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], 14);
	delay(500);
}

void EtchControl::Pull()
{
	parent->RearHomeRight();

	for (double i = -1; i > -8.5; i -= .1)
	{
		parent->rearArm(i, 2, 0, 90, 90, -90);
		delay(10);
	}
	parent->rearArm(-8, 2, 0, 90, 90, -90);
	delay(1500);
	for (double i = 0; i > -3.2; i -= .05)
	{
		parent->rearArm(-8.5, 1.8, i, 90, 90, -90);
		delay(10);
	}
	parent->rearArm(-8.5, 1.8, -3.2, 90, 90, -90);
	delay(1500);

	for (double i = -8.5; i < -5; i += .05)
	{
		parent->rearArm(i, 1.8, -3.5, 90, 85, -90);
		delay(10);
	}
	delay(1500);
}


void EtchControl::Grasp()
{
	//make sure front arm is rotated so that the servo box
	// is out of the way from the rear arm.
}
