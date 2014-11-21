#include "ArmControl.h"
char temp[4] = {'b','r','g','y'};

void SimonControl::Simon_Play()
{
	Grab();
	Play();
	Release();
}

void SimonControl::Play()
{
	//hit start
	parent->Front_Smooth_Move(-1, 0, 2, 90, 90, -30, -5.2, 1.5, -2.9, 175, 90, -80, 1);
	parent->Front_Smooth_Move(-5.2, 1.5, -2.9, 175, 90, -80,-5.2, 1.5, -2, 175, 90, -80, 0.5); // come up above start

	char oneChar;
	
	//get signal from arduino
	for(int i =0; i <=3; i++)
	{
	oneChar = temp[i];
		if (oneChar == 'b')
		{
			//go to blue and back to start
			parent->Front_Smooth_Move(-5.2, 1.5, -2, 175, 90, -80, -5.2, 2.2, -2.9, 175, 90, -75, 1);
			parent->Front_Smooth_Move(-5.2, 2.2, -2.9, 175, 90, -75, -5.2, 1.5, -2, 175, 90, -80, 0.5);
		}
		if (oneChar == 'r')
		{
			//go to red and back to start
			parent->Front_Smooth_Move(-5.2, 1.5, -2, 175, 90, -80, -5.2, 1.5, -2.9, 175, 90, -100, 1);
			parent->Front_Smooth_Move(-5.2, 1.5, -2.9, 175, 90, -100, -5.2, 1.5, -2, 175, 90, -80, 0.5);
		}
		if (oneChar == 'g')
		{
			//go to green and back to start
			parent->Front_Smooth_Move(-5.2, 1.5, -2, 175, 90, -80, -5.2, 0.5, -2.9, 175, 90, -90, 1);
			parent->Front_Smooth_Move(-5.2, 0.5, -2.9, 175, 90, -90, -5.2, 1.5, -2, 175, 90, -80, 0.5);
		}
		if (oneChar == 'y')
		{
			//go to yellow and back to start
			parent->Front_Smooth_Move(-5.2, 1.5, -2, 175, 90, -80, -5.2, 0.9, -3.1, 175, 90, -60, 1);
			parent->Front_Smooth_Move(-5.2, 0.9, -3.1, 175, 90, -60, -5.2, 1.5, -2, 175, 90, -80, 0.5);
		}
	}
	
}


void SimonControl::Grab()
{
	double gripAngle = 70;
	parent->RearHomeLeft();
	parent->frontHomeLeft();
	parent->Rear_Smooth_Move(1, 0, 2, gripAngle, 90, -30, 8.5, 3, -2.3, gripAngle, 100, -90, 1);
	parent->Rear_Smooth_Move(8.5, 3, -2.3, gripAngle, 100, -90, 7.1, 3, -2.6, gripAngle, 90, -100, 1);

}

void SimonControl::Release()
{
	double gripAngle = 70;
	parent->Front_Smooth_Move(-5.2, 1.5, -2, 175, 90, -80, -1, 0, 2, 90, 90, -30, 1);
	parent->Rear_Smooth_Move(7.1, 3, -2.6, gripAngle, 90, -100, 3.4,2.5,-1,gripAngle,110,-110,1);
	parent->Rear_Smooth_Move(3.4,2.5,-1,gripAngle,110,-110,3.4,2.5,-1,0,110,-110,1);
	parent->Rear_Smooth_Move(3.4,2.5,-1,0,110,-110,3.4,2.5,0,0,110,-110,1);
	parent->Rear_Smooth_Move(3.4,2.5,0,0,110,-110,1,0,2,90,90,-30,1);
	parent->RearHomeLeft();
	parent->RearFlipToRight();
	parent->RearHomeRight();
	parent->frontHomeLeft();
	parent->FrontFlipToRight();
	parent->frontHomeRight();
}
