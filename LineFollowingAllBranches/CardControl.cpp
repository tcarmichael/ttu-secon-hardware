#include "ArmControl.h"

void CardControl::Card_Play()
{

	parent->frontHomeRight();
	parent->Front_Smooth_Move(1, 0, 2, 90, 90, -30, 8, 2, -5.6, 90, 80, -10, 1.5);
	delay(500);
	parent->Front_Smooth_Move(8, 2, -5.6, 90, 80, -10, 8, 2, -6, 90, 80, 0, 1.5);
	parent->Front_Smooth_Move(8, 2, -6, 90, 80, 0, 1, 0, 2, 90, 80, -60, 1.5);
}
