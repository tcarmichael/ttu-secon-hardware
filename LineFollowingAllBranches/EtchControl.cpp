#include "ArmControl.h"
#include "Arduino.h"

void EtchControl::Etch_Play()
{
	Pull();
	Grasp();
	delay(timing);
	draw();
	Release();
}
void EtchControl::draw()
{
	// assumes the knobs have already been grasped with the
	// front arm rotated with the servo box away from the rear arm
	letterI();
	makeSpace();
	makeSpace();
	letterE();
	makeSpace();
	makeSpace();
	letterE();
	makeSpace();
	makeSpace();
	letterE();
	makeSpace();
	makeSpace();
}

void EtchControl::makeSpace()
{
	// new letter

	// Release knob
	parent->setPosition(parent->Rear_Arm[5], openRearGripper);
	delay(timing);

	// Rotate wrist
	parent->setPosition(parent->Rear_Arm[4], 175);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Rear_Arm[5], closeRearGripper);
	delay(timing);

	// Scroll over
	parent->setPosition(parent->Rear_Arm[4], 14);
	delay(timing);

	// Release knob
	parent->setPosition(parent->Rear_Arm[5], openRearGripper);
	delay(timing);

	// Rotate wrist
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Rear_Arm[5], closeRearGripper);
	delay(timing);
}

void EtchControl::letterI()
{
	// draw I
	parent->setPosition(parent->Rear_Arm[4], 175);
	delay(timing);
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 85);
	delay(timing);

	down();
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 170);
	delay(timing);

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
		delay(timing);

		// Horizontal back
		parent->setPosition(parent->Rear_Arm[4], 180);
		count = 1;
		down();
	}

	parent->setPosition(parent->Rear_Arm[4], 40);
}

void EtchControl::down()
{
	int rotate = 175;
	if (count == 1)
	{
		rotate = 120;
	}


	// Vertical line
	// Release knob
	parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(timing);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], rotate);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], closeFrontGripper);
	delay(timing);

	// Scroll over
	parent->setPosition(parent->Front_Arm[4], 14);
	delay(timing);


}


void EtchControl::Pull()
{
	double TimeConstant = .7;
	// move both arms out
	double A011[6] = { -1, 0, 2, 50, 90, -30 };
	double C011[6] = { -8.5, 0.5, -4.5, 50, 0, -90 };
	double M011[6] = { 1, 0, 2, 90, 90, -30 };
	double N011[6] = { 8.5, 1.5, -4.5, 90, 0, -90 };


	parent->Both_Smooth_Move(A011, C011, M011, N011, TimeConstant);

	delay(1000);
	// move both arms back to robot
	double A01[6] = { -8.5, 0.5, -4.5, 50, 0, -90 };
	double C01[6] = { -4.2, 0.5, -5, 50, 0, -100 };
	double M01[6] = { 8.5, 1.5, -4.5, 90, 0, -90 };
	double N01[6] = { 4, 1.5, -5, 90, 0, -100 };
	parent->Both_Smooth_Move(A01, C01, M01, N01, TimeConstant);
	delay(100);

	//fudging
	double A0111[6] = { -4.2, 0.5, -5, 50, 90, -100 };
	double C0111[6] = { -4.2, 0.5, -5, 50, 130, -100 };
	double M0111[6] = { 4, 1.5, -5, 90, 90, -100 };
	double N0111[6] = { 4, 1.5, -5, 90, 40, -100 };
	//parent->Both_Smooth_Move(A0111, C0111, M0111, N0111, TimeConstant);
	//delay(100);


	// move away to prepare to grab knobs
	double A[6] = { -4.5, 0.5, -5, 50, 0, -90 };
	double B[6] = { -6, 0.5, -3, 50, 90, -90 };
	double M[6] = { 4.2, 1.5, -5, 90, 0, -90 };
	double N[6] = { 6, 1.5, -3, 90, 90, -90 };


	parent->Both_Smooth_Move(A, B, M, N, TimeConstant);
}


void EtchControl::Grasp()
{
	double TimeConstant = .8;
	// move both arms to knobs
	double A011[6] = { -6, 0.5, -3, 50, 90, -90 };
	double C011[6] = { -5.5, 0, -4, 50, 90, -100 };
	double M011[6] = { 6, 1.5, -3, 90, 90, -90 };
	double N011[6] = { 5.55, 1.3, -4, 90, 90, -102 };


	parent->Both_Smooth_Move(A011, C011, M011, N011, TimeConstant);
	//make sure front arm is rotated so that the servo box
	// is out of the way from the rear arm.
	delay(100);
	parent->setPosition(4, 30);
	delay(100);
	parent->setPosition(5, closeRearGripper);
	delay(100);
	parent->setPosition(parent->Front_Arm[4], 14);
	delay(100);
	parent->setPosition(14,closeFrontGripper);

}

void EtchControl::Release()
{
	double TimeConstant = .5;
	// pull etch away
	double A011[6] = { -5.5, 0, -4, closeRearGripper, 90, -90 };
	double C011[6] = { -7.5, 0, -4, closeRearGripper, 90, -100 };
	double M011[6] = { 5.55, 1.3, -4, closeFrontGripper, 90, -102 };
	double N011[6] = { 7.55, 1.3, -4, closeFrontGripper, 90, -102 };
	parent->Both_Smooth_Move(A011, C011, M011, N011, TimeConstant);

	//move arms to home
	double A[6] = { -7.5, 0, -4, closeRearGripper, 90, -100 };
	double C[6] = { -1, 0, 2, 90, 90, -30 };
	double M[6] = { 7.55, 1.3, -4, closeFrontGripper, 90, -102 };
	double N[6] = { 1, 0, 2, 90, 90, -30 };
	parent->Both_Smooth_Move(A, C, M, N, TimeConstant);

    //move arms to left side
	parent->FrontFlipToLeft();
	delay(100);
	parent->frontHomeLeft();
	delay(100);
	parent->RearFlipToLeft();
	delay(100);
	parent->RearHomeLeft();
	delay(100);

}