#include "ArmControl.h"


void RubiksControl::Grab()
{
	parent->Front_Smooth_Move(-1, 0, 2, 90, 90, -30,-1, 0, 2, 90, 90, 90,1); //move front arm out of the way
	parent->Rear_Smooth_Move(1, 0, 2, 90, 90, -30, 3.9, 2.2, -0.1, 90, 0, -90,1); //move rear arm to grab rubik hat
	delay(1500);
	parent->Rear_Smooth_Move(3.9, 2.2, -0.1, 90, 0, -90, 3.9, 2.2, -1.1, 90, 0, -90,1); //move rear arm to grab rubik hat
	delay(1500);
	parent->Rear_Smooth_Move(3.9, 2.2, -1.1, 90, 0, -90, 3.9, 2.2, -0.9, 117, 0, -90,1); //move rear arm to grab rubik hat
	delay(1500);
	parent->Rear_Smooth_Move(3.9, 2.2, -1.1, 117, 0, -90, 1, 0, 2, 117, 0, 90,1); //move rear arm to grab rubik hat
	parent->Front_Smooth_Move(-1, 0, 2, 90, 90, 90, -9, 2, 0, 90, 90, -90, 1); //extend front arm out to rubik
	parent->Front_Smooth_Move(-9, 2, 0, 90, 90, -90, -9, 2, -2, 90, 90, -90, 1);//low arm to grab rubik
	parent->Front_Smooth_Move(-9, 2, -2, 90, 90, -90, -7, 2, -2, 90, 90, -90, 1); //bring rubik into skid
	//parent->Front_Smooth_Move(
}


void RubiksControl::Rotate()
{
	parent->Rear_Smooth_Move(4, 0, 2, 90, 30, -90, 4, 0, 2, 90, 90, -90, 1); //move rear arm out of the way, holding hat
	delay(1500);


	parent->Rear_Smooth_Move(4, 0, 2, 90, 90, -90, 5.2, 2.5, 0, 95, 30, -100, 1); //move rear arm over rubik
	delay(1500);


	parent->Rear_Smooth_Move(5.2, 2.5, 0, 95, 30, -100, 4.5, 2.5, -.8, 95, 30, -100, 1); //bring hat onto rubik
	delay(1500);

	// Fudge factoring

	parent->Rear_Smooth_Move(4.5, 2.5, -.8, 95, 30, -100, 4.5, 2.3, -.8, 95, 30, -100, 1); //really make sure hat is there
	delay(1500);



	parent->Rear_Smooth_Move(4.8, 2.5, -.8, 95, 30, -100, 4.8, 2.5, -.8, 95, 30, -100, 1); //
	delay(1500);
	parent->Rear_Smooth_Move(4.8, 2.5, -.8, 95, 30, -100, 4.2, 2.5, -.8, 95, 180, -100, 1);
	delay(1500);

	// loose grip 
	parent->Rear_Smooth_Move(4.2, 2.5, -.8, 95, 180, -100, 4.2, 2.5, -.8, 0, 180, -100, 1);
	delay(1500);

	// Move up 
	parent->Rear_Smooth_Move(4.2, 2.5, -.8, 0, 180, -100, 4.2, 2.5, 1, 0, 30, -100, 1);
	delay(1500);

	// rotate
	parent->Rear_Smooth_Move(4.2, 2.5, 1, 95, 30, -100, 4.2, 2.5, 1, 95, 30, -100, 1);
	delay(1500);
}

void RubiksControl::Release()
{
	
}

