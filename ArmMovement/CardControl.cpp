#include "ArmControl.h"

void CardControl::Card_Play()
{
	parent->RearHomeRight();
	parent->frontHomeRight();
	parent->Rear_Smooth_Move(-1, 0, 2, 90, 90, -30, -8, 2, -5, 90, 90, -25, 1.5);
	delay(500);
	parent->Rear_Smooth_Move(-8, 2, -5, 90, 90, -20, -1, 0, 2, 90, 90, -60,  1.5);
}
