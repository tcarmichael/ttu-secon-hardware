#include "ArmControl.h"

void CardControl::Play()
{
	double GripConstant = 100;
	/*
parent->frontHomeRight();
	parent->Front_Smooth_Move(1, 0, 2, 90, 90, -30,               7, 2, -5.6, 90, 90, -10, .7); // extend arm over card
	delay(500);
	parent->Front_Smooth_Move(7, 2, -5.6, 90, 90, -10,                   6, 2, -7, 90, 90, 0, .7); // lower arm to card
	delay(500);
	parent->Front_Smooth_Move(  6, 2, -7, 90, 90, 0,                       6, 2, -7, 90, 90, -20, .7); //put pressure on card
	delay(500); 
	parent->Front_Smooth_Move(6, 2, -7, 90, 90, -20,					6, 2, -7, 90, 90, 0, 0.7); //slowly lift up
	delay(100);
	parent->Front_Smooth_Move(  6, 2, -7,  90, 90, -20,                    6, 2, 2,  90, 90, -60, .3);//bring card back to robot
	parent->Front_Smooth_Move( 6, 2, 2,  90, 90, -60,                   1, 0, 2, 90, 90, -65, .3);
	*/
	parent->Rear_Smooth_Move(-1, 0, 2, GripConstant, 90, -30,               -7, 2, -5.6, GripConstant, 90, -10, .7); // extend arm over card
	delay(500);
	parent->Rear_Smooth_Move(-7, 2, -5.6, GripConstant, 90, -10,                   -6, 2, -7, GripConstant, 10, 0, .7); // lower arm to card
	delay(500);
	parent->Rear_Smooth_Move( - 6, 2, -7, GripConstant, 10, 0,                      - 6, 2, -7, GripConstant, 10, -20, .7); //put pressure on card
	delay(500); 
	parent->Rear_Smooth_Move(-6, 2, -7, GripConstant, 10, -20,					-6, 2, -7, GripConstant, 10, 0, 0.7); //slowly lift up
	delay(100);
	parent->Rear_Smooth_Move( - 6, 2, -7,  GripConstant, 10, -20,                   - 6, 2, 2,  GripConstant, 10, -60, .3);//bring card back to robot
	parent->Rear_Smooth_Move( -6, 2, 2,  GripConstant, 10, -60,                 -  1, 0, 2, GripConstant, 10, -75, .3);
	
}
