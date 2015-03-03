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
	double TimeConstant=.6;
	
	
	parent->frontHomeLeft();
	parent->RearHomeLeft();



	//grab hat from skid
	/*

	
	double A001[6]={1, 0, 2, 90, 90, -30};
	double C001[6]={ 3.9, 2.2, -0.1, 20, 120, -105};
	double M001[6]={-1, 0, 2, 90, 90, -30};
	double N001[6]={  -1, 0, 2, 90, 90, 90};


	parent->Both_Smooth_Move(A001,C001,M001,N001,TimeConstant);


	//parent->Front_Smooth_Move(-1, 0, 2, 90, 90, -30,    -1, 0, 2, 90, 90, 90,    TimeConstant); //move front arm out of the way
	//delay(100);
	
	//parent->Rear_Smooth_Move(1, 0, 2, 90, 90, -30,     3.9, 2.2, -0.1, 20, 120, -105,   TimeConstant); //move rear arm to grab rubik hat - above it
	//delay(100);
	
	parent->Rear_Smooth_Move(3.9, 2.2, -0.1, 20, 120, -105,      4.0, 2.5, -3.1, 0, 120, -105,    TimeConstant); //move rear arm to grab rubik hat -bend to it
	delay(100);

	parent->Rear_Smooth_Move(4.0, 2.5, -3.1, 0, 120, -105,      4.0, 2.5, -3.1, 110, 120, -105,      TimeConstant); //move rear arm to grab rubik hat -grasp it
	delay(100);

	parent->Rear_Smooth_Move(4.1, 2.5, -3.1, 110, 120, -105,       4.1, 2.5, 0, 110, 120, -105,      TimeConstant); //squeeze
	delay(100);

	*/


	// Forcing Rubiks to center position


	// move both arms out
	double A011[6] = { 1, 0, 2, 110, 90, -30 }; // savannah changed 4.1, 2.5, 0, 110, 120, -105
	double C011[6]={  8, 0, 0, 110, 90, -105};
	double M011[6]={-1, 0, 2, 90, 90, -30};
	double N011[6]={ -9, 0, 0, 0, 180, -105};


	parent->Both_Smooth_Move(A011,C011,M011,N011,TimeConstant);
	

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
	double B[6]={8.5, 1.4, -4.3, 110, 92, -105};
	double M[6]={-9, 0, -4.3, 0, 185, -105};
	double N[6]={-9, 1, -4.3, 0, 185, -105};


	parent->Both_Smooth_Move(A,B,M,N,TimeConstant);
	delay(100);
	
	// Pull out
	double A2[6] = { 8.5, 1.4, -4.3, 110, 92, -105 };
	double B2[6] = { 8.5, 0.5, -4.3, 110, 92, -105 }; //8.5, 0, -4.3, 110, 92, -105 savannah changed
	double M2[6] = { -8.5, 1, -4.3, 0, 185, -105 };
	double N2[6]={-9, 0, -4.3, 0, 185, -105};


	parent->Both_Smooth_Move(A2,B2,M2,N2,TimeConstant);
	delay(100);
	// Pull in setup
	double A3[6] = { 8.5, 0.5, -4.3, 110, 92, -105 }; //8.5, 0, -4.3, 110, 92, -105 savannah changed
	double B3[6] = { 8.5, 0, -4.3, 110, 92, -105 }; //6, 0, 2, 110, 92, -105}; savannah changed
	double M3[6]={-9, 0, -4.3, 0, 185, -105};
	double N3[6]={-9, 0, -3, 0, 185, 0};


	parent->Both_Smooth_Move(A3,B3,M3,N3,TimeConstant);
	delay(100);
	
	// Pull in setup step 2
	parent->Front_Smooth_Move(-9, 0, -3, 0, 163, 0,           -9, 2, -5, 0, 90, 0, TimeConstant);
	delay(100);
	
	// pull in wrist swing down
	parent->Front_Smooth_Move(-9, 2, -5, 0, 90, 0, -9, 1.5, -5, 0, 78, -90, TimeConstant);
	delay(100);

	
	// pull in x direction  -savannah commented it out
	//parent->Front_Smooth_Move(-9, 2, -5, 0, 78, -90, -5, 2, -5, 0, 78, -90, TimeConstant);
	//delay(100);
	//savannah added this 
	double A33[6] = { 8.5, 0.5, -4.3, 110, 92, -105 }; 
	double B33[6] = { 6, 0, 2, 110, 92, -105 }; 
	double M33[6] = { -9, 2, -5, 0, 78, -90 };
	double N33[6] = { -5, 2, -5, 0, 74, -90 }; //Savannah changed this from 78
	parent->Both_Smooth_Move(A33, B33, M33, N33, TimeConstant);


	// move out the way
	parent->Front_Smooth_Move(-7, 2, -4, 0, 83, -90,           -8, 0, -5, 0, 83, 90, TimeConstant);
	delay(100);

	
	// Place hat position
	double A4[6]={6, 0, 2, 110, 92, -105};
	double B4[6]={4.7, 2.9, -2, 110, 33, -105};
	double M4[6]={ -8, 0, -5, 0, 83, 90};
	double N4[6]={-1, 0, 2, 90, 90, 90};


	parent->Both_Smooth_Move(A4,B4,M4,N4,TimeConstant);
	
	

	
	
}


void RubiksControl::Rotate()
{
	double TimeConstant=.4;
	// place hat on it
	parent->Rear_Smooth_Move(4.7, 2.9, -2, 110, 33, -105,                        4.7, 2.5, -2.7, 110, 33, -105,                      TimeConstant); 
	delay(100);

	// Fudge factoring
	parent->Rear_Smooth_Move( 4.7, 3.1, -2.5, 110, 33, -105,                          4.7, 2.3, -2.3, 110, 33, -105,                        TimeConstant); //really make sure hat is there
	delay(100);
	parent->Rear_Smooth_Move( 4.5, 2.5, -2.5, 110, 33, -105,                          4.9, 2.5, -2.5, 110, 33, -105,                        TimeConstant); //really make sure hat is there
	delay(100);

	parent->Rear_Smooth_Move(4.7, 2.9, -2.5, 110, 33, -105,                        4.3, 2.9, -3, 110, 33, -105,                      TimeConstant); //Push hat down and back
	delay(100);
	

	//// rotating
	//savannah changed this from 4.8 to 4.3
	parent->Rear_Smooth_Move(  4.5, 2.9, -3, 110, 33, -105,                     4.3, 2.9, -2.7, 110, 180, -105,  TimeConstant);                               //rotate hat
	delay(100);


	//reset hat
	parent->Rear_Smooth_Move(4.5, 2.9, -2.5, 110, 180, -105,                  4.5, 2.9, -2.5, 0, 180, -105,           TimeConstant); //open grip
	delay(100);
	parent->Rear_Smooth_Move(4.5, 2.9, -2.5, 0, 180, -105,                     4.5, 2.9, -2, 0, 180, -105,           TimeConstant); //move up
	delay(100);
	parent->Rear_Smooth_Move(4.5, 2.9, -2, 0, 180, -105,                        4.5, 2.9, -2, 0, 0, -105,           TimeConstant); //reset wrist
	delay(100);
	parent->Rear_Smooth_Move(  4.5, 2.9, -2, 0, 0, -105,                4.5, 2.9, -3, 0, 0, -105,           TimeConstant); //lower
	delay(100);
	parent->Rear_Smooth_Move(   4.5, 2.9, -3, 0, 0, -105,                4.5, 2.9, -3, 110, 0, -105,           TimeConstant); //squeeze
	delay(100);
	parent->Rear_Smooth_Move(    4.5, 2.9, -3, 110, 0, -105,               4.3, 2.9, -3, 110, 0, -105,           TimeConstant); // pull back just in case
	delay(100);


	//changed 4.6 t0 4.3 by savannah
	// rotate again
	parent->Rear_Smooth_Move(  4.3, 2.9, -3, 110, 0, -105,               4.1, 2.9, -3, 105, 40, -105,           TimeConstant); //rotate
	delay(100);


}

void RubiksControl::Release()
{
	double TimeConstant=.4;
	// ditch hat and cube
	parent->Rear_Smooth_Move(  4.6, 2.9, -3, 105, 70, -105,                  8.5, 2.9, -3, 105, 70, -105,           TimeConstant); //pull out
	delay(100);

	parent->Rear_Smooth_Move(   8.5, 2.9, -3, 105, 70, -105,                  8.5, 2.9, -3, 105, 110, -105,           TimeConstant); //rotate cube
	delay(100);

	parent->Rear_Smooth_Move(     8.5, 2.9, -3, 105, 110, -105,                   8.5, 2.9, 1, 105, 110, -105,           TimeConstant); //pull up
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

