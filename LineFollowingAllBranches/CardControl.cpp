#include "ArmControl.h"

void CardControl::Card_Play()
{

parent->frontHomeRight();
	parent->Front_Smooth_Move(1, 0, 2, 90, 90, -30,               7, 2, -5.6, 90, 90, -10, .7); // extend arm over card
	delay(500);
	parent->Front_Smooth_Move(7, 2, -5.6, 90, 90, -10,                   6, 2, -7, 90, 90, 0, .7); // lower arm to card
	delay(500);
	parent->Front_Smooth_Move(  6, 2, -7, 90, 90, 0,                       6, 2, -7, 90, 90, -20, .7); //put pressure on card
	delay(500); //bring card back to robot
	parent->Front_Smooth_Move(6, 2, -7, 90, 90, -20,					6, 2, -7, 90, 90, 0, 0.7);
	delay(100);
	parent->Front_Smooth_Move(  6, 2, -7,  90, 90, -20,                    6, 2, 2,  90, 90, -60, .3);
	parent->Front_Smooth_Move( 6, 2, 2,  90, 90, -60,                   1, 0, 2, 90, 90, -65, .3);
}
