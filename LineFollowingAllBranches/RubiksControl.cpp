#include "ArmControl.h"

double gripAngle = 115;
void RubiksControl::Play()
{
	Grab();
	Rotate();
	Release();
}
void RubiksControl::Grab()
{
	double TimeConstant=.6;

	double GripConstant = 100;
	
	//parent->frontHomeLeft();
	parent->RearHomeLeft();




	// Forcing Rubiks to center position

	/*
	// move both arms out
	double A011[6] = { 1, 0, 2, GripConstant, 90, -30 }; // savannah changed 4.1, 2.5, 0, GripConstant, 120, -105
	double C011[6]={  8, 0, 0, GripConstant, 90, -105};
	double M011[6]={-1, 0, 2, 90, 90, -30};
	double N011[6]={ -9, 0, 0, 0, 180, -105};


	parent->Both_Smooth_Move(A011,C011,M011,N011,0.3);
	*/
	parent->Rear_Smooth_Move(1, 0, 2, GripConstant, 90, -30  ,     8, 0, 0, GripConstant, 90, -105,.3);

	//parent->Rear_Smooth_Move(4.1, 2.5, 0, GripConstant, 120, -105,         8, 0, 0, GripConstant, 90, -105, TimeConstant); //move rear arm up out 
	
/*
	
// move both arms down
	double A01[6]={8, 0, 0, GripConstant, 90, -105};
	double C01[6]={ 8, 0, -4, GripConstant, 90, -105};
	double M01[6]={-9, 0, 0, 0, 180, -105};
	double N01[6]={ -9, 0, -4.3, 0, 185, -105};


	parent->Both_Smooth_Move(A01,C01,M01,N01,.3);
	
	
// Squeeze together
	double A[6]={8.0, 0, -4, GripConstant, 92, -105};
	double B[6]={8.5, 1.1, -4.3, GripConstant, 92, -105};
	double M[6]={-9, 0, -4.3, 0, 185, -105};
	double N[6]={-9, .5, -4.3, 0, 185, -105};


	parent->Both_Smooth_Move(A,B,M,N,.4);
	

	// Pull out
	double A2[6] = { 8.5, 1.1, -4.3, GripConstant, 92, -105 };
	double B2[6] = { 8.5, 0, -4.3, GripConstant, 92, -105 };
	double M2[6] = { -9, .5, -4.3, 0, 185, -105 };
	double N2[6] = { -9, 0, -4.3, 0, 185, -105 };


	parent->Both_Smooth_Move(A2, B2, M2, N2, 0.3);
	

	
	// Pull in setup
	double A3[6] = { 8.5, 0, -4.3, GripConstant, 92, -105 };
	double B3[6] = { 8.5, 0, -3, GripConstant, 92, 0 };
	double M3[6] = { -9, 0, -4.3, 0, 185, -105 };
	double N3[6] = { -1, 0, 2, 90, 90, 90 };


	parent->Both_Smooth_Move(A3, B3, M3, N3, 0.3);
	*/
	//Pull in setup just rear
	parent->Rear_Smooth_Move(8, 0, 0, GripConstant, 90, -105, 8.5, 3, -4, GripConstant, 100, 0, 0.3);

	
	// Pull in setup step 2
	//parent->Rear_Smooth_Move(8.5, 0, -3, GripConstant, 92, 0, 8.5, 3, -4, GripConstant, 100, 0, 0.3);
	

	// pull in wrist swing down
	parent->Rear_Smooth_Move(8.5, 2.9, -4, GripConstant, 100, 0, 8.5, 2.9, -4, GripConstant, 110, -100, .9);
	//continued swing and lower in z
	parent->Rear_Smooth_Move(8.5, 2.9, -4, GripConstant, 110, -100, 8.5, 2.9, -5, GripConstant, 110, -115, .7);

	
	//move away and up from cube
	parent->Rear_Smooth_Move( 8.5, 2.9, -5, GripConstant, 110, -115, 8.5, 2.9, -2.5, GripConstant, 110, -110,0.3);

	//reset hat wrist
	parent->Rear_Smooth_Move(8.5, 2.9, -2.5, GripConstant, 110, -110,8.5, 2.9, -2.5, GripConstant, 20, -110, 0.1);

	//theta in and x in and z down to catch cube
	parent->Rear_Smooth_Move( 8.5, 2.9, -2.5, GripConstant, 20, -110, 7.5, 3.4, -2.6, GripConstant, 21, -129,0.3);

	//in x and let theta out to grab hat
	parent->Rear_Smooth_Move(7.5, 3.4, -2.6, GripConstant, 21, -129, 4.9, 2.1, -2.7, GripConstant, 21, -110,0.3);
	
	
}


void RubiksControl::Rotate()
{
	double TimeConstant=.4;
	// place hat on it
	double GripConstant = 100; 
	double wristConstant = 21;
	

	//// rotating 90 degrees
	parent->Rear_Smooth_Move(4.9, 2.1, -2.7, GripConstant, 21, -110, 4.9, 2.1, -2.7, GripConstant, 130, -110, TimeConstant);   

	//move up from cube
	parent->Rear_Smooth_Move( 4.9, 2.1, -2.7, GripConstant, 130, -110, 4.9, 2.1, 0, GripConstant, 110, -110,0.3);

	//move away 
	parent->Rear_Smooth_Move(4.9, 2.1, 0, GripConstant, 110, -110, 8.5, 2.9, -2.5, GripConstant, 110, -110,0.3);


	//reset hat wrist
	parent->Rear_Smooth_Move(8.5, 2.9, -2.5, GripConstant, 110, -110,8.5, 2.9, -2.5, GripConstant, 20, -110, 0.1);

	//theta in and x in and z down to catch cube
	parent->Rear_Smooth_Move( 8.5, 2.9, -2.5, GripConstant, 20, -110, 7.5, 3.4, -2.6, GripConstant, 21, -129,0.3);

	//in x and let theta out to grab hat
	parent->Rear_Smooth_Move(7.5, 3.4, -2.6, GripConstant, 21, -129, 4.9, 2.1, -2.71, GripConstant, 21, -110,0.3);

		//// rotating 90 degrees
		//savannah changed this from 4.8 to 4.3
		parent->Rear_Smooth_Move(4.9, 2.1, -2.71, GripConstant, 21, -110, 4.9, 2.1, -2.71, GripConstant, 130, -110, TimeConstant);

}

void RubiksControl::Release()
{
	double TimeConstant=.4;
	double GripConstant = 100;
	// ditch hat and cube
	parent->Rear_Smooth_Move( 4.9, 2.1, -2.7, GripConstant, 130, -110,           8.5, 2.9, -3.2, GripConstant, 115, -105,           TimeConstant); //pull out  CHANGING 140 rotate
	
	//parent->Rear_Smooth_Move(   8.5, 2.9, -3, GripConstant, 140, -105,                  8.5, 2.9, -3, GripConstant, 33, -105,           TimeConstant); //rotate cube
	//delay(100);

	parent->Rear_Smooth_Move(     8.5, 2.9, -3, GripConstant, 115, -105,                   8.5, 2.9, 1, GripConstant, 115, -105,           TimeConstant); //pull up
	parent->Rear_Smooth_Move(      8.5, 2.9, 1, GripConstant, 115, -105,                   1, 0, 2, GripConstant, 90, -30,           TimeConstant); //pull up

	parent->RearFlipToRight();
	parent->RearHomeRight();
	//parent->frontHomeLeft();
	//parent->FrontFlipToRight();
	//parent->frontHomeRight();
	
}

