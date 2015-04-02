#include "ArmControl.h"
#include "Arduino.h"

void EtchControl::Play()
{
	Pull();
	Grasp();
	delay(timing);
	draw();
	Release();
}
void EtchControl::draw()
{
	// assumes the knobs have already been grasped with the
	// front arm rotated with the servo box away from the rear arm
	letterI();
	makeSpace();
	makeSpace();
	makeSpace();
	letterEup(); //up refers to E being draw to end up closer on the screen to the knobs than it began
	makeSpace();
	makeSpace();
	letterEdown();
	makeSpace();
	makeSpace();
	letterEup();
	makeSpace();
	makeSpace();
}

void EtchControl::makeSpace()
{
	// new letter

	// Release knob
	parent->setPosition(parent->Rear_Arm[5], openRearGripper);
	delay(timing);

	// Rotate wrist
	parent->setPosition(parent->Rear_Arm[4], 175);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Rear_Arm[5], closeRearGripper);
	delay(timing);

	// Scroll over
	parent->setPosition(parent->Rear_Arm[4], 14);
	delay(timing);

	// Release knob
	parent->setPosition(parent->Rear_Arm[5], openRearGripper);
	delay(timing);

	// Rotate wrist
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Rear_Arm[5], closeRearGripper);
	delay(timing);
}

void EtchControl::letterI()
{
	// draw I
	parent->setPosition(parent->Rear_Arm[4], 175);
	delay(timing);
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 85);
	delay(timing);

	down();
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 170);
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 30);
}

void EtchControl::letterEup()
{
	int pulselen;
	//draw E
	for (int i = 0; i < 2; i++)
	{
		 // Horizontal forward
		parent->setPosition(parent->Rear_Arm[4], 40);
		delay(timing);

		// Horizontal back
		parent->setPosition(parent->Rear_Arm[4], 180);
		count = 1;
		up();
	}

	parent->setPosition(parent->Rear_Arm[4], 40);
}

void EtchControl::letterEdown()
{
	int pulselen;
	//draw E
	for (int i = 0; i < 2; i++)
	{
		// Horizontal forward
		parent->setPosition(parent->Rear_Arm[4], 40);
		delay(timing);

		// Horizontal back
		parent->setPosition(parent->Rear_Arm[4], 180);
		count = 1;
		down();
	}

	parent->setPosition(parent->Rear_Arm[4], 40);
}



void EtchControl::down()
{
	int rotate = 175;
	if (count == 1)
	{
		rotate = 120;
	}


	// Vertical line
	// Release knob
	parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(timing);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], rotate);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], closeFrontGripper);
	delay(timing);

	// Scroll over
	parent->setPosition(parent->Front_Arm[4], 14);
	delay(timing);


}

void EtchControl::up()
{
	int rotate = 175;
	if (count == 1)
	{
		rotate = 120;
	}


	// Vertical line
	delay(timing);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], rotate);
	delay(timing);

	// Release knob
	parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(timing);

	// Scroll over
	parent->setPosition(parent->Front_Arm[4], 14);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], closeFrontGripper);
	delay(timing);


}


void EtchControl::Pull()
{
	double TimeConstant = .5;//0.3
	double GripperSqueezeHat = 100;
	

	double JusRearStart_Move1[6] = { -1, 0, 2, GripperSqueezeHat, 90, -30 };
	double JusRearEnd_Move1[6] = { -8.3, 1.3, -2.5, GripperSqueezeHat, 90, -30 };
	double JusFrontStart_Move1[6] = { 1, 0, 2, 90, 90, -30 };
	double JusFrontEnd_Move1[6] = { 1, 0, 2, 90, 90, 90 };

	parent->Both_Smooth_Move(JusRearStart_Move1, JusRearEnd_Move1, JusFrontStart_Move1, JusFrontEnd_Move1, TimeConstant); //Move front arm out of the way and rear arm out with out
	
	parent->Rear_Smooth_Move(-8.3, 1.3, -2.5, GripperSqueezeHat, 90, -30, -9, 1.3, -5, GripperSqueezeHat, 87, -70, TimeConstant);// further down
	
	parent->Rear_Smooth_Move(-9, 1.3, -5, GripperSqueezeHat, 87, -70, -9, 1.3, -4.9, GripperSqueezeHat, 87, -100, TimeConstant);// wrist rotate and theta
	
	parent->Rear_Smooth_Move(-9, 1.3, -4.9, GripperSqueezeHat, 87, -100, -7, 1.5, -4.9, GripperSqueezeHat, 87, -110, TimeConstant); // continute rotate and theta to chassis
	
	//set hat straight
	parent->Rear_Smooth_Move(-7, 1.5, -4.9, GripperSqueezeHat, 87, -110, -9, 1.5, -4, 110, 85, -110, TimeConstant); //move away
	
	parent->Rear_Smooth_Move(-9, 1.5, -4, GripperSqueezeHat, 85, -110, -9, 1.5, -5.6, GripperSqueezeHat, 85, -110, TimeConstant); //set hat

	parent->Rear_Smooth_Move(-9, 1.5, -5.6, GripperSqueezeHat, 85, -110, -8, 1.5, 0, GripperSqueezeHat, 90, -110, TimeConstant); // move away from etch
	
	
	double JusRearStart_Move2[6] = { -8, 1.5, 0, GripperSqueezeHat, 90, -110 };
	double JusRearEnd_Move2[6] = { -1, 0, 2, GripperSqueezeHat, 90, -30 };
	double JusFrontStart_Move2[6] = { 1, 0, 2, 90, 90, 90 };
	double JusFrontEnd_Move2[6] = { 1, 0, 2, 90, 90, -30 };

	parent->Both_Smooth_Move(JusRearStart_Move2, JusRearEnd_Move2, JusFrontStart_Move2, JusFrontEnd_Move2, TimeConstant);
		
	//return hat and come back
	
	parent->RearFlipToLeft();
	
	parent->RearHomeLeft();
	
	parent->Front_Smooth_Move(1, 0, 2, 90, 90, -30, 4, 0, 0, 90, 90,-90, TimeConstant); // move front arm out of the way
	
	parent->Rear_Smooth_Move(1, 0, 2, GripperSqueezeHat, 90, -30, 4.5, 2.2, -2.5, GripperSqueezeHat, 113, -110, TimeConstant); //drop hat down to right above the tabs

	delay(200);
	parent->Rear_Smooth_Move(4.5, 2.2, -2.5, GripperSqueezeHat, 113, -111, 4.2, 2.1, -2.9, GripperSqueezeHat, 113, -110, TimeConstant); //drop hat down into tabs
	delay(200);
	parent->Rear_Smooth_Move(3.8, 2.1, -3.1, GripperSqueezeHat, 113, -105, 3.8, 2.1, -3.1, 0, 113, -105, TimeConstant); // hat leggo
	delay(200);
	parent->Rear_Smooth_Move(3.8, 2.1, -3.1, 0, 113, -105, 3.8, 2.3, 0, 0, 120, -105, TimeConstant); //move up

	double JusRearStart_Move4[6] = { 3.8, 2.5, 0, 0, 120, -105 };
	double JusRearEnd_Move4[6] = { 1, 0, 2, 110, 90, -30 };
	double JusFrontStart_Move4[6] = { 4, 0, 0, 90, 90, -90 };
	double JusFrontEnd_Move4[6] = { 1, 0, 2, 90, 90, -30 };

	parent->Both_Smooth_Move(JusRearStart_Move4, JusRearEnd_Move4, JusFrontStart_Move4, JusFrontEnd_Move4, TimeConstant);
	
	parent->RearFlipToRight();
	
	parent->RearHomeRight();
	


}


void EtchControl::Grasp()
{	

	double TimeConstant = .8;


	double savA[6] = { -1, 0, 2, 90, 90, -30 };
	double savB[6] = { -6, 0, -3, 50, 90, -110 };
	double savM[6] = { 1, 0, 2, 90, 90, -30 };
	double savN[6] = { 5.5, 1.6, -3, 90, 90, -100 };


	parent->Both_Smooth_Move(savA, savB, savM, savN, TimeConstant); //prepare arms to grab knobs

	
	// move both arms to knobs
	double A011[6] = { -6, 0, -3, 50, 90, -110 };
	double C011[6] = { -6, 0.25, -4.4, 10, 30, -110 };
	double M011[6] = { 5.5, 1.6, -3, 90, 90, -100 };
	double N011[6] = { 5.8, 1.6, -4.1, 40, 14, -104 };


	parent->Both_Smooth_Move(A011, C011, M011, N011, TimeConstant);



	//Close Grippers
	double JusRearStart_Move5[6] = { -6, 0.25, -4.4, 10, 30, -110 };
	double JusRearEnd_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 30, -110 };
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4.1, 40, 14, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4.1, closeFrontGripper, 14, -104 };


	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, TimeConstant);


}

void EtchControl::Release()
{
	double TimeConstant = .5;
	// pull etch away
	double A011[6] = { -6, 0, -4.4, closeRearGripper, 30, -110 };
	double C011[6] = { -9, 0, -5, closeRearGripper, 90, -110 };
	double M011[6] = { 5.8, 1.6, -4.0, closeFrontGripper, 14, -104 };
	double N011[6] = { 8.7, 1.3, -5, closeFrontGripper, 90, -102 };
	parent->Both_Smooth_Move(A011, C011, M011, N011, TimeConstant);
	
	
	// pull etch away further
	double A012[6] = { -9, 0, -5, closeRearGripper, 90, -110 };
	double C012[6] = { -9, 0, -7, closeRearGripper, 90, -50 };
	double M012[6] = { 8.7, 1.3, -5, closeFrontGripper, 90, -102 };
	double N012[6] = { 8.7, 1.3, -7, closeFrontGripper, 90, -50 };
	parent->Both_Smooth_Move(A012, C012, M012, N012, TimeConstant);

	// release etch grip
	double A013[6] = { -9, 0, -7, closeRearGripper, 90, -50 };
	double C013[6] = { -9, 0, -7, 10, 90, -50 };
	double M013[6] = { 8.7, 1.3, -7, closeFrontGripper, 90, -50 };
	double N013[6] = { 8.7, 1.3, -7, 40, 90, -50 };
	parent->Both_Smooth_Move(A013, C013, M013, N013, TimeConstant);

	// Position Better for home return
	double A014[6] = { -9, 0, -7, 10, 90, -50 };
	double C014[6] = { -5, 0,0, 10, 90, -30 };
	double M014[6] = { 8.7, 1.3, -7, 40, 90, -50 };
	double N014[6] = { 5, 1.3, 0, 40, 90, -30 };
	parent->Both_Smooth_Move(A014, C014, M014, N014, TimeConstant);

	
	
	//move arms to home
	double A[6] = { -5, 0, 0, 10, 90, -30 };
	double C[6] = { -1, 0, 2, 90, 90, -30 };
	double M[6] = { 5, 1.3, 0, 40, 90, -30 };
	double N[6] = { 1, 0, 2, 90, 90, -30 };
	parent->Both_Smooth_Move(A, C, M, N, TimeConstant);

    //move arms to left side
	parent->FrontFlipToLeft();
	parent->frontHomeLeft();
	parent->RearFlipToLeft();
	parent->RearHomeLeft();


	//grab hat from skid
	double A001[6] = { 1, 0, 2, 90, 90, -30 };
	double C001[6] = { 3.9, 2.2, -0.1, 20, 120, -105 };
	double M001[6] = { -1, 0, 2, 90, 90, -30 };
	double N001[6] = { -1, 0, 2, 90, 90, 90 };
	parent->Both_Smooth_Move(A001, C001, M001, N001, TimeConstant);
	parent->Rear_Smooth_Move(3.9, 2.2, -0.1, 20, 120, -105, 4.1, 2.2, -3.1, -5, 120, -107, TimeConstant+0.6); //move rear arm to grab rubik hat -bend to it
	delay(500);
	parent->Rear_Smooth_Move(4.1, 2.2, -3.1, -5, 120, -107, 3.99, 2.2, -3.3, 110, 120, -105, TimeConstant); //move rear arm to grab rubik hat -grasp it
	delay(500);
	parent->Rear_Smooth_Move(3.98, 2.2, -3.2, 110, 120, -105, 4.1, 2.4, 0, 110, 120, -105, TimeConstant); //lift hat up
	delay(100);
	parent->RearHomeLeft();
	parent->frontHomeLeft();
	


}