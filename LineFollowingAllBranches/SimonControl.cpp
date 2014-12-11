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
	double TimeConstant = .5;
	//hit start
	delay(1000);
	parent->Front_Smooth_Move(-4, 1.5, -3.7, 180, 70, -70, -4.6, 1.5, -4.2, 180, 70, -95, TimeConstant);
	parent->Front_Smooth_Move(-4.6, 1.5, -4.2, 180, 70, -95, -4, 1.5, -3.3, 180, 70, -70, TimeConstant);

	char oneChar;
	
	//get signal from arduino
	for(int i =0; i <=3; i++)
	{
	oneChar = temp[i];
		if (oneChar == 'b')
		{
			//go to blue and back to start
			parent->Front_Smooth_Move(-4, 1.5, -3.3, 180, 70, -70, -4.6, 3, -4.6, 180, 70, -95, TimeConstant);
			parent->Front_Smooth_Move(-4.6, 3, -4.3, 180, 70, -95, -4, 1.5, -3.3, 180, 70, -70, TimeConstant);
		}
		if (oneChar == 'r')
		{
			//go to red and back to start
			parent->Front_Smooth_Move(-4, 1.5, -3.3, 180, 70, -70, -1.5, 1.5, -4.1, 180, 70, -95, TimeConstant);
			parent->Front_Smooth_Move(-1.5, 1.5, -4.1, 180, 70, -95, -4, 1.5, -3.3, 180, 70, -70, TimeConstant);
		}
		if (oneChar == 'g')
		{
			//go to green and back to start
			parent->Front_Smooth_Move(-4, 1.5, -3.3, 180, 70, -70, -4.6, 0.5, -4, 180, 70, -95, TimeConstant);
			parent->Front_Smooth_Move(-4.6, 0.5, -4, 180, 70, -95, -4, 1.5, -3.3, 180, 70, -70, TimeConstant);
		}
		if (oneChar == 'y')
		{
			//go to yellow and back to start
			parent->Front_Smooth_Move(-4, 1.5, -3.3, 180, 70, -70, -6.7, 1.1, -4.5, 180, 70, -95, TimeConstant);
			parent->Front_Smooth_Move(-6.7, 1.1, -4.5, 180, 70, -95, -4, 1.5, -3.3, 180, 70, -70, TimeConstant);
		}
	}
	
}


void SimonControl::Grab()
{

	double TimeConstant = .5;
	parent->frontHomeLeft();
	parent->RearHomeLeft();

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
	parent->Rear_Smooth_Move(4.1, 2.5, -3.1, 110, 120, -105, 4.1, 2.5, 0, 110, 120, -105, TimeConstant); //squeeze
	delay(100);

	// Forcing simon to center position
	// move both arms out
	double A011[6] = { 4.1, 2.5, 0, 110, 120, -105 };
	double C011[6] = { 8, 0, 0, 110, 90, -105 };
	double M011[6] = { -1, 0, 2, 90, 90, 90 };
	double N011[6] = { -9, 0, 0, 0, 163, -105 };
	parent->Both_Smooth_Move(A011, C011, M011, N011, TimeConstant);
	delay(100);

	// move both arms down
	double A01[6] = { 8, 0, 0, 110, 90, -105 };
	double C01[6] = { 8, 0, -4.3, 110, 90, -105 };
	double M01[6] = { -9, 0, 0, 0, 163, -105 };
	double N01[6] = { -9, 0, -5.6, 0, 163, -105 };
	parent->Both_Smooth_Move(A01, C01, M01, N01, TimeConstant);
	delay(100);

	// Squeeze together
	double A[6] = { 8.5, 0, -4.3, 110, 92, -105 };
	double B[6] = { 8.5, 1.6, -4.3, 110, 92, -105 };
	double M[6] = { -8.5, 0, -5.6, 0, 163, -105 };
	double N[6] = { -8.5, .7, -5.6, 0, 163, -105 };


	parent->Both_Smooth_Move(A, B, M, N, TimeConstant);
	delay(100);

	// Pull out
	double A2[6] = { 8.5, 1.7, -4.3, 110, 92, -105 };
	double B2[6] = { 8.5, 0, -4.3, 110, 92, -105 };
	double M2[6] = { -8.5, .6, -5.6, 0, 163, -105 };
	double N2[6] = { -9, 0, -5, 0, 163, -105 };


	parent->Both_Smooth_Move(A2, B2, M2, N2, TimeConstant);
	delay(100);
	// Pull in setup
	double A3[6] = { 8.5, 0, -4.3, 110, 92, -105 };
	double B3[6] = { 7.5, 0, -5, 110, 92, -105 };
	double M3[6] = { -9, 0, -4.3, 0, 163, -105 };
	double N3[6] = { -9, 0, -4.5, 0, 163, -50 };


	parent->Both_Smooth_Move(A3, B3, M3, N3, TimeConstant);
	delay(100);
	// Pull in setup step 2
	parent->Front_Smooth_Move(-9, 0, -4.5, 0, 163, -50, -9, 2, -5, 0, 80, -50, TimeConstant);
	delay(100);

	// pull in wrist swing down
	parent->Front_Smooth_Move(-9, 2, -5, 0, 80, -50, -9, 2, -5, 50, 65, -90, TimeConstant);
	delay(100);

	// pull in x direction 
	parent->Front_Smooth_Move(-9, 2, -5, 0, 65, -90, -5, 2, -5, 50, 65, -90, TimeConstant);
	delay(100);

	//move front arm out of the way
	parent->Front_Smooth_Move(-5, 2, -5, 50, 65, -90, -7, 2, -5, 50, 65, -90, TimeConstant);
	delay(100);
	parent->Front_Smooth_Move(-7, 2, -5, 50, 65, -90, -4, 1.5, -3.7, 180, 70, -70, TimeConstant);

	//move rear arm to hold simon
	parent->Rear_Smooth_Move(7.5, 0, -5, 110, 92, -105, 8.5, 2, -5, 110, 130, -105, TimeConstant);
	delay(100);
	parent->Rear_Smooth_Move(8.5, 2, -5, 110, 130, -105, 7, 2, -5, 110, 130, -105, TimeConstant);
	delay(100);

}

void SimonControl::Release()
{
	double TimeConstant = .5;

	//take hat to skid and move front arm home
	double A001[6] = { 7, 2, -5, 110, 130, -105 };
	double C001[6] = { 7, 0, -5, 110, 130, -105 };
	double M001[6] = { -4, 1.5, -3.3, 180, 70, -70 };
	double N001[6] = { -2, 1.5, -3.6, 180, 70, -70 }; //push simon out
	parent->Both_Smooth_Move(A001, C001, M001, N001, TimeConstant);
	parent->Front_Smooth_Move(-2, 1.5, -3.6, 180, 70, -70, -4, 0, -2, 180, 70, -70, TimeConstant);
	delay(100);
	parent->Front_Smooth_Move(-4, 0, -2, 180, 70, -70, -1, 0, 2, 90, 90, -30, TimeConstant);
	delay(100);
	parent->Front_Smooth_Move(-1, 0, 2, 90, 90, -30, -1, 0, 2, 90, 90, 90, TimeConstant);
	delay(100);
	parent->Rear_Smooth_Move(7, 0, -5, 110, 130, -105, 4.0, 2.5, -2, 110, 120, -105, TimeConstant);
	delay(100);

	parent->Rear_Smooth_Move(4.0, 2.5, -2, 110, 120, -105, 4, 2.5, -3.1, 110, 120, -105, TimeConstant); //drop hat down
	delay(100);

	parent->Rear_Smooth_Move(4, 2.5, -3.1, 110, 120, -105, 4, 2.5, -3.1, 0, 120, -105, TimeConstant); // hat leggo
	delay(100);

	parent->Rear_Smooth_Move(4, 2.5, -3.1, 110, 120, -105, 4, 2.5, 2, 0, 120, -105, TimeConstant); //move up
	delay(100);


	parent->RearHomeLeft();
	parent->frontHomeLeft();
	parent->RearFlipToRight();
	parent->RearHomeRight();
	parent->FrontFlipToRight();
	parent->frontHomeRight();
}
