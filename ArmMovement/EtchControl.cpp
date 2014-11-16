#include "ArmControl.h"

void ArmControl::EtchControl::Etch_Play()
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

void ArmControl::EtchControl::makeSpace()
{
	// new letter
	delay(3000);

	// Release knob
	parent->setPosition(Rear_Arm[5], 60);
	delay(500);

	// Rotate wrist
	parent->setPosition(Rear_Arm[4], 175);
	delay(500);

	// Grab knob
	parent->setPosition(Rear_Arm[5], 75);
	delay(500);

	// Scroll over
	parent->setPosition(Rear_Arm[4], 14);
	delay(500);

	// Release knob
	parent->setPosition(Rear_Arm[5], 60);
	delay(500);

	// Rotate wrist
	parent->setPosition(Rear_Arm[4], 180);
	delay(500);

	// Grab knob
	parent->setPosition(Rear_Arm[5], 75);
	delay(500);
}

void ArmControl::EtchControl::letterI()
{
	// draw I
	parent->setPosition(Rear_Arm[4], 30);
	delay(500);

	parent->setPosition(Rear_Arm[4], 115);
	delay(500);

	down();
	delay(500);

	parent->setPosition(Rear_Arm[4], 170);
	delay(500);

	parent->setPosition(Rear_Arm[4], 30);
}

void ArmControl::EtchControl::letterE()
{
	int pulselen;
	//draw E
	for (int i = 0; i < 2; i++)
	{
		 // Horizontal forward
		parent->setPosition(Rear_Arm[4], 40);
		delay(500);

		// Horizontal back
		parent->setPosition(Rear_Arm[4], 180);
		down();
	}

	parent->setPosition(Rear_Arm[4], 40);
}

void ArmControl::EtchControl::down()
{
	// Vertical line
	delay(1000);

	// Release knob
	parent->setPosition(Front_Arm[5], 60);
	delay(500);

	// Rotate wrist
	parent->setPosition(Front_Arm[4], 175);
	delay(500);

	// Grab knob
	parent->setPosition(Front_Arm[5], 90);
	delay(500);

	// Scroll over
	parent->setPosition(Front_Arm[4], 60);
	delay(500);

	// Release knob
	parent->setPosition(Front_Arm[5], 60);
	delay(500);

	// Rotate wrist
	parent->setPosition(Front_Arm[4], 14);
	delay(500);
}

void ArmControl::EtchControl::Pull()
{
}


void ArmControl::EtchControl::Grasp()
{
	//make sure front arm is rotated so that the servo box
	// is out of the way from the rear arm.
}
