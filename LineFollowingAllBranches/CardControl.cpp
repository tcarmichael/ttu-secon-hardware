#include "ArmControl.h"

void CardControl::Card_Play()
{

parent->frontHomeRight();
	parent->Front_Smooth_Move(1, 0, 2, 90, 90, -30,               6, 2, -5.6, 90, 80, -10, .5);
	delay(500);
	parent->Front_Smooth_Move(6, 2, -5.6, 90, 80, -10,                   5, 2, -10, 90, 70, -40, .7);
	parent->Front_Smooth_Move(  5, 2, -10, 90, 70, -40,                       5, 2, -7, 90, 70, 0, .7);
	delay(500);
	parent->Front_Smooth_Move(  5, 2, -5,  90, 70, 0,                    5, 2, 2,  90, 70, 0, .3);
	parent->Front_Smooth_Move( 5, 2, 2,  90, 70, 0,                   1, 0, 2, 90, 80, -60, .3);
}
