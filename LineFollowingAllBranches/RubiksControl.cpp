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
	
	parent->frontHomeLeft();
	parent->RearHomeLeft();




	// Forcing Rubiks to center position


	// move both arms out
	double A011[6] = { 1, 0, 2, GripConstant, 90, -30 }; // savannah changed 4.1, 2.5, 0, GripConstant, 120, -105
	double C011[6]={  8, 0, 0, GripConstant, 90, -105};
	double M011[6]={-1, 0, 2, 90, 90, -30};
	double N011[6]={ -9, 0, 0, 0, 180, -105};


	parent->Both_Smooth_Move(A011,C011,M011,N011,TimeConstant+.2);
	

	//parent->Rear_Smooth_Move(4.1, 2.5, 0, GripConstant, 120, -105,         8, 0, 0, GripConstant, 90, -105, TimeConstant); //move rear arm up out 
	

	
// move both arms down
	double A01[6]={8, 0, 0, GripConstant, 90, -105};
	double C01[6]={ 8, 0, -4, GripConstant, 90, -105};
	double M01[6]={-9, 0, 0, 0, 180, -105};
	double N01[6]={ -9, 0, -4.3, 0, 185, -105};


	parent->Both_Smooth_Move(A01,C01,M01,N01,TimeConstant);
	
	
// Squeeze together
	double A[6]={8.5, 0, -4, GripConstant, 92, -105};
	double B[6]={8.5, 1.1, -4.3, GripConstant, 92, -105};
	double M[6]={-9, 0, -4.3, 0, 185, -105};
	double N[6]={-9, .5, -4.3, 0, 185, -105};


	parent->Both_Smooth_Move(A,B,M,N,TimeConstant);
	

	// Pull out
	double A2[6] = { 8.5, 1.1, -4.3, GripConstant, 92, -105 };
	double B2[6] = { 8.5, 0, -4.3, GripConstant, 92, -105 };
	double M2[6] = { -8.5, .5, -4.3, 0, 185, -105 };
	double N2[6] = { -9, 0, -4.3, 0, 185, -105 };


	parent->Both_Smooth_Move(A2, B2, M2, N2, TimeConstant);
	

	
	// Pull in setup
	double A3[6] = { 8.5, 0, -4.3, GripConstant, 92, -105 };
	double B3[6] = { 8.5, 0, -3, GripConstant, 92, 0 };
	double M3[6] = { -9, 0, -4.3, 0, 185, -105 };
	double N3[6] = { -1, 0, 2, 90, 90, 90 };


	parent->Both_Smooth_Move(A3, B3, M3, N3, TimeConstant);
	
	
	// Pull in setup step 2
	parent->Rear_Smooth_Move(8.5, 0, -3, GripConstant, 92, 0, 8.5, 3, -4, GripConstant, 100, 0, TimeConstant);
	

	// pull in wrist swing down
	parent->Rear_Smooth_Move(8.5, 2.9, -4, GripConstant, 100, 0, 8.5, 2.9, -4, GripConstant, 110, -100, .8);
	

	parent->Rear_Smooth_Move(8.5, 2.9, -4, GripConstant, 110, -100,    6.7, 2.9, -4.5, GripConstant, 110, -110,.8); 
	
	

	// move out of the way
	parent->Rear_Smooth_Move( 6.7, 2.9, -4.5, GripConstant, 110, -110,    9, 3.1, -2, GripConstant, 110, -90, TimeConstant);
	

	//set hat straight
	parent->Rear_Smooth_Move(9, 3.1, -2, GripConstant, 110, -90, 8.9, 3.1, -5.7, GripConstant, 110, -110, TimeConstant);


	//Intermediate Step
	parent->Rear_Smooth_Move(9, 3.1, -2, GripConstant, 110, -90, 6, 2.3, 0, GripConstant, 30, -105, TimeConstant);


	//prepare to place hat
	parent->Rear_Smooth_Move(6, 2.3, 0, GripConstant, 30, -105, 4.5, 2.3, -2, GripConstant, 30, -105, TimeConstant);
	 

	
	
	
}


void RubiksControl::Rotate()
{
	double TimeConstant=.4;
	// place hat on it
	double GripConstant = 100; 
	double wristConstant = 30;
	parent->Rear_Smooth_Move(4.6, 2.3, -2, GripConstant, wristConstant, -105, 4.6, 2.4, -2.7, GripConstant, wristConstant, -105, TimeConstant);
	

	// Fudge factoring savannah changed -2.5 to -2.8
	parent->Rear_Smooth_Move(4.65, 2.4, -2.8, GripConstant, wristConstant, -105, 4.65, 2.2, -2.3, GripConstant, wristConstant, -105, TimeConstant); //really make sure hat is there
	
	parent->Rear_Smooth_Move(4.65, 2.5, -2.8, GripConstant, wristConstant, -105, 4.75, 2.5, -2.8, GripConstant, wristConstant, -105, TimeConstant); //really make sure hat is there
	
	
	parent->Rear_Smooth_Move(4.75, 2.6, -2.8, GripConstant, wristConstant, -105, 4.7, 2.6, -3, GripConstant, wristConstant, -105, TimeConstant); //Push hat down and back
	
	

	//// rotating 90 degrees
	//savannah changed this from 4.8 to 4.3
	parent->Rear_Smooth_Move(4.7, 2.6, -3, GripConstant, wristConstant, -105, 4.5, 2.6, -2.7, GripConstant, 137, -105, TimeConstant);                               //rotate hat



		parent->Rear_Smooth_Move(4.5, 2.6, -2.5, GripConstant, 137, -104, 5.6, 2.3, -2.7, GripConstant, 135, -105, TimeConstant); //so we don't move the rubiks out from the skid
		parent->Rear_Smooth_Move(5.6, 2.3, -2.7, GripConstant, 135, -105, 5.4, 2.3, -1.8, GripConstant, 135, -105, TimeConstant); //move up 4.5


		parent->Rear_Smooth_Move(4.6, 2.3, -1.8, GripConstant, wristConstant, -105, 4.65, 2.4, -2.7, GripConstant, wristConstant, -104, TimeConstant); //move down
	

		// Fudge factoring savannah changed -2.5 to -2.8
		parent->Rear_Smooth_Move(4.7, 2.4, -2.8, GripConstant, wristConstant, -104, 4.7, 2.2, -2.3, GripConstant, wristConstant, -104, TimeConstant); //really make sure hat is there
		
		parent->Rear_Smooth_Move(4.7, 2.5, -2.8, GripConstant, wristConstant, -104, 4.85, 2.5, -2.8, GripConstant, wristConstant, -104, TimeConstant); //really make sure hat is there
	

		parent->Rear_Smooth_Move(4.85, 2.6, -2.8, GripConstant, wristConstant, -104, 4.7, 2.6, -2.9, GripConstant, wristConstant, -105, TimeConstant); //Push hat down and back
		


		//// rotating 90 degrees
		//savannah changed this from 4.8 to 4.3
		parent->Rear_Smooth_Move(4.6, 2.9, -2.9, GripConstant, wristConstant, -105, 4.5, 2.9, -2.7, GripConstant, 140, -105, TimeConstant);                               //rotate hat
		

	//parent->Rear_Smooth_Move(4.5, 2.6, 2, GripConstant, 33, -105, 4.6, 2.65, -3, GripConstant, 33, -105, TimeConstant); //lower  4.5 2.9
	//delay(100);
	//parent->Rear_Smooth_Move(   4.6, 2.65, -3, 0, 0, -105,                4.6, 2.65, -3, GripConstant, 0, -105,           TimeConstant); //squeeze 4.5 2.9
	//delay(100);
	//parent->Rear_Smooth_Move(    4.6, 2.65, -3, GripConstant, 33, -105,               4.1, 2.9, -3, GripConstant, 33, -105,           TimeConstant); // pull back just in case
	//delay(100);

	/*
	//changed 4.6 t0 4.3 by savannah
	// rotate again
	parent->Rear_Smooth_Move(  4.3, 2.9, -3, GripConstant, 0, -105,               4.1, 2.9, -3, 105, 59, -105,           TimeConstant); //rotate
	delay(100);
	*/

}

void RubiksControl::Release()
{
	double TimeConstant=.4;
	double GripConstant = 100;
	// ditch hat and cube
	parent->Rear_Smooth_Move(  4.6, 2.9, -3.1, GripConstant, 140, -105,                  8.5, 2.9, -3.2, GripConstant, 115, -105,           TimeConstant); //pull out
	

	//parent->Rear_Smooth_Move(   8.5, 2.9, -3, GripConstant, 140, -105,                  8.5, 2.9, -3, GripConstant, 33, -105,           TimeConstant); //rotate cube
	//delay(100);

	parent->Rear_Smooth_Move(     8.5, 2.9, -3, GripConstant, 115, -105,                   8.5, 2.9, 1, GripConstant, 115, -105,           TimeConstant); //pull up
	

	parent->Rear_Smooth_Move(      8.5, 2.9, 1, GripConstant, 115, -105,                   1, 0, 2, GripConstant, 90, -30,           TimeConstant); //pull up
	

	/*parent->Rear_Smooth_Move(   9, 2.9, 2, GripConstant, 70, -105,                   4.0, 2.5, -2, GripConstant, 120, -105,      TimeConstant); //place back hat
	delay(1000);

	parent->Rear_Smooth_Move(    4.0, 2.5, -2, GripConstant, 120, -105,             4.4, 2.5, -3.1, GripConstant, 120, -105,       TimeConstant); //drop hat down
	delay(1000);

	parent->Rear_Smooth_Move(     4.4, 2.5, -3.1, GripConstant, 120, -105,         4.4, 2.5, -3.1, 0, 120, -105,       TimeConstant); // hat leggo
	delay(1000);

	parent->Rear_Smooth_Move(    4.4, 2.5, -3.1, GripConstant, 120, -105,             4.2, 2.5, 2, 0, 120, -105,       TimeConstant); //move up
	delay(100);*/
	
	parent->RearHomeLeft();
	parent->frontHomeLeft();
	parent->FrontFlipToRight();
	parent->frontHomeRight();
	
}

