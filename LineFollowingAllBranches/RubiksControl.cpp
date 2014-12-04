#include "ArmControl.h"

double gripAngle = 115;
void RubiksControl::Rubiks_Play()
{
	Grab();
	Rotate();
	Release();
}
void RubiksControl::Grab()
{
	
	//grab hat from skid
	parent->frontHomeLeft();
	parent->RearHomeLeft();
	parent->Front_Smooth_Move(-1, 0, 2, 90, 90, -30,-1, 0, 2, 90, 90, 90,1); //move front arm out of the way

	parent->Rear_Smooth_Move(1, 0, 2, 90, 90, -30, 3.9, 2.2, -0.1, 20, 90, -90,1); //move rear arm to grab rubik hat - above it
	delay(1500);
	parent->Rear_Smooth_Move(3.9, 2, -0.1, 20, 90, -90, 3.2, 2, -1.1, 20, 90, -90,1); //move rear arm to grab rubik hat -bend to it
	delay(1500);
	parent->Rear_Smooth_Move(3.2, 2, -1.1, 20, 90, -90, 3.2, 2, -0.9, gripAngle, 90, -90,1); //move rear arm to grab rubik hat -grasp it
	delay(1500);
	parent->Rear_Smooth_Move(3.2, 2, -1.1, gripAngle,90, -90, 1, 0, 2, gripAngle, 90, 90,1); //move rear arm to out of the way
	
	//grab rubik
	parent->Front_Smooth_Move(-1, 0, 2, 85, 90, 90, -8.5, 1.5, 0, 90, 90, -50, 1); //extend front arm out to rubik
	parent->Front_Smooth_Move(-8.5, 1.5, 0, 90, 90, -50, -8.5, 1.4, -3.5, 90, 65, -90, 1);//low arm to grab rubik
	delay(500);
	parent->Front_Smooth_Move(-8.5, 1.4, -3.5, 90, 65, -90, -6.6, 1.4, -3, 90, 65, -90, 1); //bring rubik into skid
	delay(500);
	parent->Front_Smooth_Move(-6.6, 1.5, -3, 90, 65, -90, -6.6, 1.5, 0, 90, 65, -90, 1); // rise above cube
	delay(500);
	parent->Front_Smooth_Move(-6.6, 1.5, 0, 90, 65, -90, -1, 0, 2, 90, 90, 90, 1); //return to home and out of the way
}


void RubiksControl::Rotate()
{
	//parent->frontHomeLeft(); //testing only
	parent->Rear_Smooth_Move(1, 0, 2, gripAngle, 0, 90, 4, 0, 2, gripAngle, 90, -90, 1); //move rear arm 
	delay(1500);
	parent->Rear_Smooth_Move(4, 0, 2, gripAngle, 90, -90, 5.2, 2.5, 0, gripAngle, 30, -100, 1); //move rear arm over rubik
	delay(1500);
	parent->Rear_Smooth_Move(5.2, 2.5, 0, gripAngle, 30, -100, 4.5, 2.5, -.8, gripAngle, 30, -100, 1); //bring hat onto rubik
	delay(1500);
	// Fudge factoring
	parent->Rear_Smooth_Move(4.5, 2.5, -.8, gripAngle, 30, -100, 4.5, 2.3, -.8, gripAngle, 30, -100, 1); //really make sure hat is there
	delay(1500);


	parent->Rear_Smooth_Move(4.8, 2.5, -.8, gripAngle, 30, -100, 4.2, 2.5, -.8, gripAngle, 136, -100, 1); //rotate hat
	delay(1500);

	//reset hat
	parent->Rear_Smooth_Move(4.2, 2.5, -.8, gripAngle, 140, -100, 4.2, 2.5, 0, gripAngle, 140, -100, 1); //lift hat up
	parent->Rear_Smooth_Move(4.2, 2.5, 0, gripAngle, 140, -100, 5.2, 2.5, 0, gripAngle, 30, -100, 1); //reset hat
	parent->Rear_Smooth_Move(5.2, 2.5, 0, gripAngle, 30, -100, 4.5, 2.5, -.8, gripAngle, 30, -100, 1); //bring hat onto rubik
	delay(1500);
	// Fudge factoring
	parent->Rear_Smooth_Move(4.5, 2.5, -.8, gripAngle, 30, -100, 4.5, 2.3, -.8, gripAngle, 30, -100, 1); //really make sure hat is there
	delay(1500);
	parent->Rear_Smooth_Move(4.8, 2.5, -.8, gripAngle, 30, -100, 4.2, 2.5, -.8, gripAngle, 136, -100, 1); //rotate hat
	delay(1500);


}

void RubiksControl::Release()
{
	parent->Rear_Smooth_Move(4.2, 2.5, -.8, gripAngle, 140, -100, 4.2, 2.5, 0, gripAngle, 140, -100, 1); //lift hat up
	parent->Rear_Smooth_Move(4.2, 2.5, 0, gripAngle, 140, -100, 1, 0, 2, gripAngle, 0, -30, 1); //return to home
	parent->frontHomeLeft();
	parent->FrontFlipToRight();
	parent->frontHomeRight();
	
}

