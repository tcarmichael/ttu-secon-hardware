#include "ArmControl.h"
#include "Arduino.h"

void EtchControl::Play()
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
	makeSpace();
	letterEup(); //up refers to E being draw to end up closer on the screen to the knobs than it began
	makeSpace();
	makeSpace();
	letterEdown();
	makeSpace();
	makeSpace();
	letterEup();
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

void EtchControl::letterEup()
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
		up();
	}

	parent->setPosition(parent->Rear_Arm[4], 40);
}

void EtchControl::letterEdown()
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

void EtchControl::up()
{
	int rotate = 175;
	if (count == 1)
	{
		rotate = 120;
	}


	// Vertical line
	delay(timing);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], rotate);
	delay(timing);

	// Release knob
	parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(timing);

	// Scroll over
	parent->setPosition(parent->Front_Arm[4], 14);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], closeFrontGripper);
	delay(timing);


}


void EtchControl::Pull()
{
	double TimeConstant = 1;//0.3
	parent->Front_Smooth_Move(1, 0, 2, 90, 90, -30, 1, 0, 2, 90, 90, 90, TimeConstant);


	parent->Rear_Smooth_Move(-1, 0, 2, 110, 90, -30,   -8.3, 1.5, -2.5, 110, 90, -30, TimeConstant);// setup and grip hat
	parent->Rear_Smooth_Move(-8.3, 1.5, -2.5, 110, 90, -30, -9, 1.5, -5, 110, 90, -70, TimeConstant);// further down
	parent->Rear_Smooth_Move(-9, 1.5, -5, 110, 90, -70, -9, 1.5, -5, 110, 84, -100, TimeConstant);// wrist rotate and theta
	parent->Rear_Smooth_Move(-9, 1.5, -5, 110, 85, -100, -9, 1.5, -5, 110, 84, -130, 2); // continute rotate and theta to chassis
	
	//set hat straight
	parent->Rear_Smooth_Move(-9, 1.5, -5, 110, 80, -130, -9, 1.5, -5, 110, 85, -110, TimeConstant); //move away
	parent->Rear_Smooth_Move(-9, 1.5, -5, 110, 85, -110, -9, 1.5, -5.3, 110, 85, -110, TimeConstant); //set hat


	parent->Rear_Smooth_Move(-9, 1.5, -5.1, 110, 85, -110, - 8.3, 1.5, -2.5, 110, 90, -30, TimeConstant); // move away from etch
	parent->Rear_Smooth_Move(-8.3, 1.5, -2.5, 110, 90, -30, -1, 0, 2, 110, 90, -30, TimeConstant); // return to home position
	parent->frontHomeRight(); //move front arm back down

	//return hat and come back
	parent->RearHomeRight();
	delay(100);
	parent->RearFlipToLeft();
	delay(100);
	parent->RearHomeLeft();
	delay(100);
	parent->Front_Smooth_Move(1, 0, 2, 90, 90, -30, 4, 0, 3, 90, 90, -30, TimeConstant); // move front arm out of the way
	delay(100);
	parent->Rear_Smooth_Move(1, 0, 2, 110, 90, -30, 4.5, 2.8, -2.5, 110, 123, -111, TimeConstant); //drop hat down to right above the tabs
	delay(100);
	
	parent->Rear_Smooth_Move(4.5, 2.8, -2.5, 110, 123, -111, 4.5, 2.8, -3.7, 110, 123, -111, TimeConstant); //drop hat down into tabs
	delay(100);
	
	
	//fudge factoring
	//parent->Rear_Smooth_Move(3.8, 2.5, -2.9, 110, 132, -105, 3.6, 2.4, -2.9, 110, 120, -105, TimeConstant); //move around a little bit
	//delay(100);

	
	parent->Rear_Smooth_Move(3.8, 2.5, -3.1, 110, 132, -105, 3.8, 2.5, -3.1, 0, 120, -105, TimeConstant); // hat leggo
	delay(100);
	parent->Rear_Smooth_Move(3.8, 2.5, -3.1, 110, 120, -105, 3.8, 2.5, -2, 0, 120, -105, TimeConstant); //move up
	delay(100);
	parent->RearHomeLeft();
	delay(100);
	parent->frontHomeRight(); // bring arm back to home
	parent->RearFlipToRight();
	delay(100);
	parent->RearHomeRight();


	double savA[6] = { -1, 0, 2, 90, 90, -30 };
	double savB[6] = { -6, 0, -3, 50, 0, -90 };
	double savM[6] = { 1, 0, 2, 90, 90, -30 };
	double savN[6] = { 6, 1.25, -3, 90, 0, -90 };


	parent->Both_Smooth_Move(savA, savB, savM, savN, TimeConstant); //prepare arms to grab knobs


	// rotate wrists
	double A4[6] = { -6, 0, -3, 50, 0, -90 };
	double B4[6] = { -6, 0, -3, 50, 90, -90 };
	double M4[6] = { 6, 1.25, -3, 90, 0, -90 };
	double N4[6] = { 6, 1.25, -3, 90, 90, -90 };

	
	parent->Both_Smooth_Move(A4, B4, M4, N4, TimeConstant);
}


void EtchControl::Grasp()
{
	double TimeConstant = .8;
	// move both arms to knobs
	double A011[6] = { -6, 0, -3, 10, 90, -90 };
	double C011[6] = { -5.5, 0, -4.1, 10, 90, -103 };
	double M011[6] = { 6, 1.25, -3, 40, 90, -90 };
	double N011[6] = { 5.55, 1.25, -4, 40, 90, -102 };


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
	delay(500);

}

void EtchControl::Release()
{
	double TimeConstant = .3;
	// pull etch away
	double A011[6] = { -5.5, 0, -4, closeRearGripper, 90, -90 };
	double C011[6] = { -7.5, 0, -4, closeRearGripper, 90, -100 };
	double M011[6] = { 5.55, 1.3, -4, closeFrontGripper, 90, -102 };
	double N011[6] = { 7.55, 1.3, -4, closeFrontGripper, 90, -102 };
	parent->Both_Smooth_Move(A011, C011, M011, N011, TimeConstant);

	//move arms to home
	double A[6] = { -7.5, 0, -4, 90, 90, -100 };
	double C[6] = { -1, 0, 2, 90, 90, -30 };
	double M[6] = { 7.55, 1.3, -4, 90, 90, -102 };
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

	//grab hat from skid
	double A001[6] = { 1, 0, 2, 90, 90, -30 };
	double C001[6] = { 3.9, 2.2, -0.1, 20, 120, -105 };
	double M001[6] = { -1, 0, 2, 90, 90, -30 };
	double N001[6] = { -1, 0, 2, 90, 90, 90 };
	parent->Both_Smooth_Move(A001, C001, M001, N001, TimeConstant);

	parent->Rear_Smooth_Move(3.9, 2.2, -0.1, 20, 120, -105, 4.0, 2.5, -3.1, 0, 120, -105, TimeConstant); //move rear arm to grab rubik hat -bend to it
	delay(100);
	parent->Rear_Smooth_Move(4.0, 2.5, -3.1, 0, 120, -105, 4.0, 2.5, -3.1, 110, 120, -105, TimeConstant); //move rear arm to grab rubik hat -grasp it
	delay(100);
	parent->Rear_Smooth_Move(4.1, 2.5, -3.1, 110, 120, -105, 4.1, 2.5, 0, 110, 120, -105, TimeConstant); //lift hat up
	delay(100);
	parent->RearHomeLeft();
	parent->frontHomeLeft();
	


}