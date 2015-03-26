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
	
	
	parent->frontHomeLeft();
	parent->RearHomeLeft();




	// Forcing Rubiks to center position


	// move both arms out
	double A011[6] = { 1, 0, 2, 110, 90, -30 }; // savannah changed 4.1, 2.5, 0, 110, 120, -105
	double C011[6]={  8, 0, 0, 110, 90, -105};
	double M011[6]={-1, 0, 2, 90, 90, -30};
	double N011[6]={ -9, 0, 0, 0, 180, -105};


	parent->Both_Smooth_Move(A011,C011,M011,N011,TimeConstant+.2);
	

	//parent->Rear_Smooth_Move(4.1, 2.5, 0, 110, 120, -105,         8, 0, 0, 110, 90, -105, TimeConstant); //move rear arm up out 
	delay(100);

	
// move both arms down
	double A01[6]={8, 0, 0, 110, 90, -105};
	double C01[6]={ 8, 0, -4, 110, 90, -105};
	double M01[6]={-9, 0, 0, 0, 180, -105};
	double N01[6]={ -9, 0, -4.3, 0, 185, -105};


	parent->Both_Smooth_Move(A01,C01,M01,N01,TimeConstant);
	delay(100);
	
// Squeeze together
	double A[6]={8.5, 0, -4, 110, 92, -105};
	double B[6]={8.5, 2, -4.3, 110, 92, -105};
	double M[6]={-9, 0, -4.3, 0, 185, -105};
	double N[6]={-9, .5, -4.3, 0, 185, -105};


	parent->Both_Smooth_Move(A,B,M,N,TimeConstant);
	delay(100);

	// Pull out
	double A2[6] = { 8.5, 2, -4.3, 110, 92, -105 };
	double B2[6] = { 8.5, 0, -4.3, 110, 92, -105 };
	double M2[6] = { -8.5, .5, -4.3, 0, 185, -105 };
	double N2[6] = { -9, 0, -4.3, 0, 185, -105 };


	parent->Both_Smooth_Move(A2, B2, M2, N2, TimeConstant);
	delay(100);

	
	// Pull in setup
	double A3[6] = { 8.5, 0, -4.3, 110, 92, -105 };
	double B3[6] = { 8.5, 0, -3, 110, 92, 0 };
	double M3[6] = { -9, 0, -4.3, 0, 185, -105 };
	double N3[6] = { -1, 0, 2, 90, 90, 90 };


	parent->Both_Smooth_Move(A3, B3, M3, N3, TimeConstant);
	delay(100); 
	
	// Pull in setup step 2
	parent->Rear_Smooth_Move(8.5, 0, -3, 110, 92, 0, 8.5, 3, -4, 110, 100, 0, TimeConstant);
	delay(100); 

	// pull in wrist swing down
	parent->Rear_Smooth_Move(8.5, 3, -4, 110, 100, 0, 8.5, 3.2, -4, 110, 115, -100, .8);
	delay(100); 

	parent->Rear_Smooth_Move(8.5, 3.2, -4, 110, 115, -100,    6.7, 3.2, -4.5, 110, 115, -110,.8); 
	delay(1000);
	

	// move out of the way
	parent->Rear_Smooth_Move( 6.7, 3.2, -4.5, 110, 118, -110,    9, 3.2, -2, 110, 115, -90, TimeConstant);
	delay(100);

	//set hat straight
	parent->Rear_Smooth_Move(9, 3.2, -2, 110, 115, -90, 9, 3.2, -5.5, 110, 115, -110, TimeConstant);
	delay(1000);

	//Intermediate Step
	parent->Rear_Smooth_Move(9, 3.2, -2, 110, 115, -90, 6, 2.9, 0, 110, 33, -105, TimeConstant);
	delay(100); 

	//prepare to place hat
	parent->Rear_Smooth_Move(6, 2.9, 0, 110, 33, -105, 4.5, 2.9, -2, 110, 33, -105, TimeConstant);
	delay(100); 

	
	
	
}


void RubiksControl::Rotate()
{
	double TimeConstant=.4;
	// place hat on it
	parent->Rear_Smooth_Move(4.5, 2.9, -2, 110, 33, -105,                        4.5, 2.5, -2.7, 110, 33, -105,                      TimeConstant); 
	delay(100);

	// Fudge factoring savannah changed -2.5 to -2.8
	parent->Rear_Smooth_Move( 4.5, 3.1, -2.8, 110, 33, -105,                          4.5, 2.3, -2.3, 110, 33, -105,                        TimeConstant); //really make sure hat is there
	delay(100);
	parent->Rear_Smooth_Move( 4.5, 2.5, -2.8, 110, 33, -105,                          4.9, 2.5, -2.8, 110, 33, -105,                        TimeConstant); //really make sure hat is there
	delay(100);
	
	parent->Rear_Smooth_Move(4.5, 2.9, -2.8, 110, 33, -105,                        4.3, 2.9, -3, 110, 33, -105,                      TimeConstant); //Push hat down and back
	delay(100);
	

	//// rotating
	//savannah changed this from 4.8 to 4.3
	parent->Rear_Smooth_Move(  4.5, 2.9, -3, 110, 33, -105,                     4.1, 2.9, -2.7, 110, 180, -105,  TimeConstant);                               //rotate hat
	delay(100);


	//reset hat
	parent->Rear_Smooth_Move(4.5, 2.6, -2.5, 110, 180, -105,                  4.5, 2.6, -2.5, 0, 180, -105,           TimeConstant); //open grip 4.5
	delay(100);
	parent->Rear_Smooth_Move(4.5, 2.6, -2.5, 0, 180, -105,                     4.5, 2.6, 2, 0, 180, -105,           TimeConstant); //move up 4.5
	delay(100);
	parent->Rear_Smooth_Move(4.5, 2.6, 2, 0, 180, -105,                        4.5, 2.6, 2, 0, 0, -105,           TimeConstant); //reset wrist
	delay(100);
	parent->Rear_Smooth_Move( 4.5, 2.6, 2, 0, 0, -105,                4.6, 2.65, -3, 0, 0, -105,           TimeConstant); //lower  4.5 2.9
	delay(100);
	parent->Rear_Smooth_Move(   4.6, 2.65, -3, 0, 0, -105,                4.6, 2.65, -3, 110, 0, -105,           TimeConstant); //squeeze 4.5 2.9
	delay(100);
	parent->Rear_Smooth_Move(    4.6, 2.65, -3, 110, 0, -105,               4.1, 2.9, -3, 110, 0, -105,           TimeConstant); // pull back just in case
	delay(100);


	//changed 4.6 t0 4.3 by savannah
	// rotate again
	parent->Rear_Smooth_Move(  4.3, 2.9, -3, 110, 0, -105,               4.1, 2.9, -3, 105, 59, -105,           TimeConstant); //rotate
	delay(100);
	


}

void RubiksControl::Release()
{
	double TimeConstant=.4;
	// ditch hat and cube
	parent->Rear_Smooth_Move(  4.6, 2.9, -3.1, 105, 59, -105,                  8.5, 2.9, -3, 105, 70, -105,           TimeConstant); //pull out
	delay(100);

	parent->Rear_Smooth_Move(   8.5, 2.9, -3, 105, 70, -105,                  8.5, 2.9, -3, 105, 110, -105,           TimeConstant); //rotate cube
	delay(100);

	parent->Rear_Smooth_Move(     8.5, 2.9, -3, 105, 110, -105,                   8.5, 2.9, 1, 105, 110, -105,           TimeConstant); //pull up
	delay(100);

	parent->Rear_Smooth_Move(      8.5, 2.9, 1, 105, 110, -105,                   1, 0, 2, 110, 90, -30,           TimeConstant); //pull up
	delay(100);

	/*parent->Rear_Smooth_Move(   9, 2.9, 2, 110, 70, -105,                   4.0, 2.5, -2, 110, 120, -105,      TimeConstant); //place back hat
	delay(1000);

	parent->Rear_Smooth_Move(    4.0, 2.5, -2, 110, 120, -105,             4.4, 2.5, -3.1, 110, 120, -105,       TimeConstant); //drop hat down
	delay(1000);

	parent->Rear_Smooth_Move(     4.4, 2.5, -3.1, 110, 120, -105,         4.4, 2.5, -3.1, 0, 120, -105,       TimeConstant); // hat leggo
	delay(1000);

	parent->Rear_Smooth_Move(    4.4, 2.5, -3.1, 110, 120, -105,             4.2, 2.5, 2, 0, 120, -105,       TimeConstant); //move up
	delay(100);*/
	
	parent->RearHomeLeft();
	parent->frontHomeLeft();
	parent->FrontFlipToRight();
	parent->frontHomeRight();
	
}

