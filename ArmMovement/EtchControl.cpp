#include "ArmControl.h"
#include "Arduino.h"

void EtchControl::Etch_Play()
{
	Pull();
	Grasp();
	draw();
	Release();
}
void EtchControl::draw()
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
	parent->setPosition(parent->Rear_Arm[5], openRearGripper);
	delay(500);

	// Rotate wrist
	parent->setPosition(parent->Rear_Arm[4], 175);
	delay(500);

	// Grab knob
	parent->setPosition(parent->Rear_Arm[5], closeRearGripper);
	delay(500);

	// Scroll over
	parent->setPosition(parent->Rear_Arm[4], 14);
	delay(500);

	// Release knob
	parent->setPosition(parent->Rear_Arm[5], openRearGripper);
	delay(500);

	// Rotate wrist
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(500);

	// Grab knob
	parent->setPosition(parent->Rear_Arm[5], closeRearGripper);
	delay(500);
}

void EtchControl::letterI()
{
	// draw I
	parent->setPosition(parent->Rear_Arm[4], 175);
	delay(500);

	parent->setPosition(parent->Rear_Arm[4], 85);
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
	delay(500);

	// Release knob
	parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(500);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], 175);
	delay(500);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], closeFrontGripper);
	delay(500);

	// Scroll over
	parent->setPosition(parent->Front_Arm[4], 14);
	delay(500);

	// Release knob
	/*parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(500);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], 14);
	delay(500);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], closeFrontGripper);
	delay(500);*/
}

void EtchControl::Pull()
{
	parent->frontHomeRight();
	parent->RearHomeRight();
	parent->Rear_Smooth_Move(-1, 0, 2, 90, 90, -30, -8.5, 2, 0, 90, 90, -90, 1.5); 
	parent->rearArm(-8, 2, 0, 90, 90, -90);
	delay(1500);
	parent->Rear_Smooth_Move(-8.5, 1.8, 0, 90, 90, -90,-8.5, 1.8, -3.2, 90, 90, -90, 1.5); 
	parent->rearArm(-8.5, 1.8, -3.2, 90, 90, -90);
	delay(1500);
	parent->Rear_Smooth_Move(-8.5, 1.8, -3.5, 90, 80, -90, -5, 1.8, -3.5, 90, 70, -90, 1.5);
	delay(1500);
	parent->Rear_Smooth_Move(-5, 1.8, -3.5, 90, 85, -90, -5, 1.8, -2, 90, 85, -90, 1.5);
	delay(1500);
}


void EtchControl::Grasp()
{
	parent->rearArm(-5, .4, 0, 90, 90, -90);
	delay(1500);
	parent->Rear_Smooth_Move(-5, .4, 0, 90, 90, -90, -6.4, 0.25, -1.95, 30, 100, -100, 1.5); 
	delay(1500);
	parent->setPosition(5,closeRearGripper);

	parent->frontArm(5, 1.8, 0, 90, 90, -90);
	delay(1500);
	parent->Front_Smooth_Move(5, 1.6, 0, 90, 90, -90, 4.85, 1.4, -2.5, 30, 5, -85, 1.5); 
	delay(1500);
	parent->setPosition(14,closeFrontGripper);
	parent->setPosition(4,30);
	//make sure front arm is rotated so that the servo box
	// is out of the way from the rear arm.

}

void EtchControl::Release()
{
	parent->Front_Smooth_Move(4.85, 1.4, -2.5, 30, 5, -85, 5,1.6,0,90,90,-90,1.5);
	parent->frontHomeRight();
	parent->Rear_Smooth_Move( -6.4, 0.25, -1.95, closeRearGripper, 100, -100 ,-7.5, .4, -1.95, closeRearGripper, 90, -90, 1.5);
	parent->Rear_Smooth_Move(-7.5, .4, -1.95, 90, 90, -90, -7,.4, 0, 90, 90, -90,1.5);
	delay(500);
	parent->RearHomeRight(); //move arms to left side
	delay(500);
	parent->frontHomeRight();
	delay(500);
	parent->FrontFlipToLeft();
	delay(500);
	parent->frontHomeLeft();
	delay(500);
	parent->RearFlipToLeft();
	delay(500);
	parent->RearHomeLeft();
	delay(500);

}