#include "ArmControl.h"


void SimonControl::Play()
{
	//return arms to home, but move to right side
	Grab();
}


void SimonControl::Grab()
{
	parent->frontHomeLeft();
	parent->RearHomeLeft();
	parent->Rear_Smooth_Move(1, 0, 2, 90, 90, -30, -8.5, 2, 0, 90, 90, -90, 1.5);
	parent->rearArm(8, 2, 0, 90, 90, -90);
	delay(1500);
	parent->Rear_Smooth_Move(8.5, 1.8, 0, 90, 90, -90, -8.5, 1.8, -3.2, 90, 90, -90, 1.5);
	parent->rearArm(8.5, 1.8, -3.2, 90, 90, -90);
	delay(1500);
	parent->Rear_Smooth_Move(8.5, 1.8, -3.5, 90, 80, -90, -5, 1.8, -3.5, 90, 70, -90, 1.5);
	delay(1500);
	parent->Rear_Smooth_Move(5, 1.8, -3.5, 90, 85, -90, -5, 1.8, -2, 90, 85, -90, 1.5);
	delay(1500);
}
