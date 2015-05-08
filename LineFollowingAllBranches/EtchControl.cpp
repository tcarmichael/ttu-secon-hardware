#include "ArmControl.h"
#include "Arduino.h"

void EtchControl::Play()
{
	//Pull();
	Grasp();
	delay(timing);
	draw_savannah();
	//draw();
	//Release();
}
void EtchControl::draw()
{
	// assumes the knobs have already been grasped with the
	// front arm rotated with the servo box away from the rear arm
	int count;
	count = letterIdown();
	makeSpace();
	count = letterEup(); //up refers to E being draw to end up closer on the screen to the knobs than it began
	makeSpace();
	count = letterEdown();
	makeSpace();
	count = letterEup();

}

void EtchControl::draw_savannah()
{


	/*letterSdown();
	letterAup();
	makeSpace();
	letterVdown();
	makeSpace();
	letterAup();
	makeSpace();
	letterNdown();
	makeSpace();
	letterNup();
	makeSpace();
	letterAup();
	makeSpace();
	letterHdown();*/


}

int EtchControl::letterAup()
{
	resetRearRight();
	resetFrontRight();
	//make first leg
	double JusRearStart_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusRearEnd_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4, closeFrontGripper, 14, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4, closeFrontGripper, 130, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);
	//reset arms
	double JusRearStart_Move51[6] = { -6, 0.25, -4.4, openRearGripper, 90, -110 };
	double JusRearEnd_Move51[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusFrontStart_Move5111[6] = { 5.8, 1.6, -4, openFrontGripper, 130, -104 };
	double JusFrontEnd_Move51[6] = { 5.8, 1.6, -4, closeFrontGripper, 14, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move51, JusRearEnd_Move51, JusFrontStart_Move5111, JusFrontEnd_Move51, 0.5);
	//make first leg
	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);

	//go back to middle
	double JusRearStart_Move52[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusRearEnd_Move52[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusFrontStart_Move5112[6] = { 5.8, 1.6, -4, closeFrontGripper, 130, -104 };
	double JusFrontEnd_Move52[6] = { 5.8, 1.6, -4, closeFrontGripper, 14, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move52, JusRearEnd_Move52, JusFrontStart_Move5112, JusFrontEnd_Move52, 0.5);

	//cross of A
	resetRearLeft();
	delay(timing * 4);
	parent->setPosition(parent->Rear_Arm[4], 100);
	delay(timing * 3);
	resetRearRight();


	//move to top of A
	resetFrontLeft();
	double JusRearStart_Move53[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusRearEnd_Move53[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move5113[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move53[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move53, JusRearEnd_Move53, JusFrontStart_Move5113, JusFrontEnd_Move53, 0.5);

	//move back to middle of right of A
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	//reset arms
	double JusRearStart_Move88[6] = { -6, 0.25, -4.4, openRearGripper, 40, -110 };
	double JusRearEnd_Move88[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move88[6] = { 5.8, 1.6, -4, openFrontGripper, 175, -104 };
	double JusFrontEnd_Move88[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move88, JusRearEnd_Move88, JusFrontStart_Move88, JusFrontEnd_Move88, 0.5);

	//finish A
	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	return 1;
}

int EtchControl::letterAdown()
{
	resetRearLeft();
	resetFrontLeft();
	//make first leg
	double JusRearStart_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4, closeFrontGripper, 59, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);
	//reset arms
	double JusRearStart_Move51[6] = { -6, 0.25, -4.4, openRearGripper, 130, -110 };
	double JusRearEnd_Move51[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusFrontStart_Move5111[6] = { 5.8, 1.6, -4, openFrontGripper, 59, -104 };
	double JusFrontEnd_Move51[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move51, JusRearEnd_Move51, JusFrontStart_Move5111, JusFrontEnd_Move51, 0.5);
	//make first leg
	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);

	//go back to middle
	double JusRearStart_Move52[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusRearEnd_Move52[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusFrontStart_Move5112[6] = { 5.8, 1.6, -4, closeFrontGripper, 59, -104 };
	double JusFrontEnd_Move52[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move52, JusRearEnd_Move52, JusFrontStart_Move5112, JusFrontEnd_Move52, 0.5);

	//cross of A
	resetRearLeft();
	delay(timing * 2);
	parent->setPosition(parent->Rear_Arm[4], 100);
	delay(timing * 3);
	resetRearRight();


	//move to top of A
	resetFrontLeft();
	double JusRearStart_Move53[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusRearEnd_Move53[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move5113[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move53[6] = { 5.8, 1.6, -4, closeFrontGripper, 70, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move53, JusRearEnd_Move53, JusFrontStart_Move5113, JusFrontEnd_Move53, 0.5);

	//move back to middle of right of A
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 70, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	//reset arms
	double JusRearStart_Move88[6] = { -6, 0.25, -4.4, openRearGripper, 40, -110 };
	double JusRearEnd_Move88[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move88[6] = { 5.8, 1.6, -4, openFrontGripper, 175, -104 };
	double JusFrontEnd_Move88[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move88, JusRearEnd_Move88, JusFrontStart_Move88, JusFrontEnd_Move88, 0.5);

	//finish A
	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	return 1;
}

int EtchControl::letterBdown()
{
	resetRearLeft();
	resetFrontLeft();
	down();
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 60);
	for (int i = 0; i < 2; i++)
	{
		up();
		delay(timing);
		parent->setPosition(parent->Rear_Arm[4], 100);
		delay(timing);
		parent->setPosition(parent->Rear_Arm[4], 180);
		delay(timing);
		parent->setPosition(parent->Rear_Arm[4], 100);
		delay(timing);
		parent->setPosition(parent->Rear_Arm[4], 60);
		if (i == 0)
		{
			up();
			delay(timing);
		}
	}
	delay(timing);
	return 1;
}

int EtchControl::letterBup()
{
	resetRearLeft();
	resetFrontLeft();
	for (int i = 0; i < 2; i++)
	{
		parent->setPosition(parent->Rear_Arm[4], 60);
		down();
		parent->setPosition(parent->Rear_Arm[4], 100);
		delay(timing);
		parent->setPosition(parent->Rear_Arm[4], 180);
		delay(timing * 2);
	}
	up();
	delay(timing * 2);
	up();
	delay(timing * 2);
	up();
	parent->setPosition(parent->Front_Arm[4], 25);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	return 1;
}

int EtchControl::letterCdown()
{
	resetRearLeft();
	delay(timing);
	resetFrontLeft();
	delay(timing * 2);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing * 2);
	down();
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 0;
}

int EtchControl::letterCup()
{
	resetRearLeft();
	delay(timing);
	resetFrontRight();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing * 2);
	up();
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 1;
}
int EtchControl::letterDdown()
{
	resetRearLeft();
	delay(timing);
	resetFrontLeft();
	delay(timing * 2);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);
	down();
	down();
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);
	up();
	delay(timing);
	up();
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);

	return 1;

}

int EtchControl::letterDup()
{
	resetRearLeft();
	delay(timing);
	resetFrontRight();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	up();
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);
	down();
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);

	return 0;

}

int EtchControl::letterEup()
{
	int pulselen;
	//draw E
	resetRearLeft();
	resetFrontRight();
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
	delay(timing);

	return 1;
}

int EtchControl::letterEdown()
{
	int pulselen;
	//draw E
	resetRearLeft();
	resetFrontLeft();

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
	delay(timing);

	return 0;
}

int EtchControl::letterFup()
{
	int pulselen;
	//draw F
	resetRearLeft();
	resetFrontRight();
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
	delay(timing);

	return 1;
}

int EtchControl::letterFdown()
{
	int pulselen;
	//draw F
	resetRearLeft();
	resetFrontLeft();
	down();
	// Horizontal forward
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	// Horizontal back
	parent->setPosition(parent->Rear_Arm[4], 180);
	count = 1;
	down();

	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 0;

}

int EtchControl::letterGup()
{
	//draw G
	resetRearLeft();
	resetFrontLeft();
	// Horizontal forward
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	// Horizontal back
	parent->setPosition(parent->Rear_Arm[4], 180);
	up();
	delay(timing);
	up();
	delay(timing);
	// Horizontal forward
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	up();
	delay(timing);

	return 1;
}

int EtchControl::letterGdown()
{
	//draw G
	resetRearLeft();
	resetFrontLeft();
	// Horizontal forward
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	up();
	delay(timing);
	// Horizontal back
	parent->setPosition(parent->Rear_Arm[4], 180);
	down();
	delay(timing);
	down();
	delay(timing);
	// Horizontal forward
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 0;

}

int EtchControl::letterHdown()
{
	resetRearLeft();
	resetFrontLeft();
	down();
	delay(timing);
	down();
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 120);
	delay(timing);
	up();
	delay(timing);
	resetFrontLeft();
	down();
	delay(timing);
	down();
	delay(timing);

	return 0;
}

int EtchControl::letterHup()
{
	resetRearLeft();
	resetFrontRight();
	up();
	delay(timing);
	up();
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 120);
	delay(timing);
	up();
	delay(timing);
	resetFrontLeft();
	down();
	down();

	return 0;
}

int EtchControl::letterIdown()
{
	resetRearLeft();
	resetFrontLeft();
	// draw I
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);

	parent->setPosition(parent->Rear_Arm[4], 130);
	delay(timing);

	down();
	delay(timing);
	down();
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	return 0;
}

int EtchControl::letterIup()
{
	resetRearLeft();
	resetFrontRight();
	// draw I
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);

	parent->setPosition(parent->Rear_Arm[4], 130);
	delay(timing);

	up();
	delay(timing);
	up();
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	return 1;
}

int EtchControl::letterJdown()
{
	resetRearLeft();
	resetFrontLeft();
	// draw J

	down();
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 110);
	delay(timing);

	down();
	delay(timing);
	down();
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 0;
}

int EtchControl::letterJup()
{
	resetRearLeft();
	resetFrontRight();
	// draw I
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);

	parent->setPosition(parent->Rear_Arm[4], 110);
	delay(timing);

	up();
	delay(timing);
	up();
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing * 2);
	down();
	up();
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);

	return 1;
}

int EtchControl::letterKdown()
{
	resetRearLeft();
	resetFrontLeft();
	down();
	delay(timing);
	down();
	delay(timing);
	up();
	delay(timing);

	//make first leg of trip up
	double JusRearStart_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4, closeFrontGripper, 59, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);

	//come back to middle
	double JusRearStart_Move51[6] = { -6, 0.25, -4.4, openRearGripper, 130, -110 };
	double JusRearEnd_Move51[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusFrontStart_Move5111[6] = { 5.8, 1.6, -4, openFrontGripper, 59, -104 };
	double JusFrontEnd_Move51[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move51, JusRearEnd_Move51, JusFrontStart_Move5111, JusFrontEnd_Move51, 0.5);

	resetFrontRight();
	//go down to end of K
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 7, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 117, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	return 1;
}

int EtchControl::letterKup()
{
	resetRearLeft();
	resetFrontRight();
	up();
	delay(timing);
	up();
	delay(timing);
	down();
	delay(timing);

	resetFrontLeft();
	//make first leg of trip up
	double JusRearStart_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4, closeFrontGripper, 59, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);

	//come back to middle
	double JusRearStart_Move51[6] = { -6, 0.25, -4.4, openRearGripper, 130, -110 };
	double JusRearEnd_Move51[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusFrontStart_Move5111[6] = { 5.8, 1.6, -4, openFrontGripper, 59, -104 };
	double JusFrontEnd_Move51[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move51, JusRearEnd_Move51, JusFrontStart_Move5111, JusFrontEnd_Move51, 0.5);

	resetFrontRight();
	//go down to end of K
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 7, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 117, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	return 1;
}

int EtchControl::letterLdown()
{
	resetFrontLeft();
	resetRearLeft();
	down();
	delay(timing);
	down();
	delay(timing);
	up();
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 1;
}

int EtchControl::letterLup()
{
	resetFrontRight();
	resetRearLeft();
	up();
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 1;
}

int EtchControl::letterMdown()
{
	resetRearLeft();
	resetFrontLeft();
	down();
	delay(timing);
	down();
	delay(timing);

	//middle part of M
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 7, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 117, -104 };
	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	//start next side of M
	resetRearLeft();
	resetFrontLeft();

	//finish middle part of M
	double JusRearStart_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4, closeFrontGripper, 59, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);

	up();
	delay(timing*2);
	up();
	delay(timing*2);

	return 1;
}

int EtchControl::letterMup()
{
	resetRearLeft();
	resetFrontRight();
	up();
	delay(timing);
	up();
	delay(timing);
	down();
	delay(timing);
	down();
	delay(timing);

	//middle part of M
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 7, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 117, -104 };
	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	//start next side of M
	resetRearLeft();
	resetFrontLeft();

	//finish middle part of M
	double JusRearStart_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4, closeFrontGripper, 59, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);

	up();
	delay(timing);
	up();
	delay(timing);

	return 1;
}

int EtchControl::letterNdown()
{
	resetRearLeft();
	resetFrontLeft();
	down();
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Front_Arm[4], 0);
	delay(timing);
	diagonalUpLtR();
	delay(timing);
	resetFrontRight();
	delay(timing);
	down();
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Front_Arm[4], 0);
	delay(timing);

	return 0;
}

int EtchControl::letterNup()
{
	resetRearLeft();
	resetFrontRight();
	up();
	delay(timing);
	resetFrontRight();
	up();
	delay(timing);
	resetFrontLeft();
	down();
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Front_Arm[4], 0);
	delay(timing);
	diagonalUpLtR();
	delay(timing);
	resetFrontRight();
	delay(timing);
	down();
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Front_Arm[4], 0);
	delay(timing);

	return 0;
}

int EtchControl::letterOdown()
{
	resetRearLeft();
	resetFrontLeft();
	down();
	delay(timing);
	down();
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	up();
	delay(timing*3);
	up();
	delay(timing*2);
	resetFrontRight();
	parent->setPosition(parent->Front_Arm[4], 60);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing*2);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 1;
}

int EtchControl::letterOup()
{
	resetRearLeft();
	resetFrontRight();
	up();
	delay(timing);
	up();
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	down();
	delay(timing);
	down();
	delay(timing*2);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing*2.5);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 0;
}

int EtchControl::letterPdown()
{
	resetRearLeft();
	resetFrontLeft();
	down();
	delay(timing);
	down();
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	down();
	delay(timing);

	return 0;
}

int EtchControl::letterPup()
{
	resetRearLeft();
	resetFrontRight();
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);
	up();
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 1;
}

int EtchControl::letterQdown()
{
	resetRearLeft();
	resetFrontLeft();
	down();
	delay(timing);
	down();
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	up();
	delay(timing);
	up();
	delay(timing);

	resetFrontLeft();
	resetRearRight();
	double JusRearStart_Move53[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusRearEnd_Move53[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move5113[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move53[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move53, JusRearEnd_Move53, JusFrontStart_Move5113, JusFrontEnd_Move53, 0.5);

	//move back to middle of right of Q
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	//reset arms
	double JusRearStart_Move88[6] = { -6, 0.25, -4.4, openRearGripper, 40, -110 };
	double JusRearEnd_Move88[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move88[6] = { 5.8, 1.6, -4, openFrontGripper, 175, -104 };
	double JusFrontEnd_Move88[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move88, JusRearEnd_Move88, JusFrontStart_Move88, JusFrontEnd_Move88, 0.5);

	//move down
	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);
	//move up
	parent->Both_Smooth_Move(JusRearStart_Move53, JusRearEnd_Move53, JusFrontStart_Move5113, JusFrontEnd_Move53, 0.5);

	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 1;
}

int EtchControl::letterQup()
{
	resetRearLeft();
	resetFrontRight();
	up();
	delay(timing);
	up();
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);

	resetFrontLeft();
	resetRearRight();
	double JusRearStart_Move53[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusRearEnd_Move53[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move5113[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move53[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move53, JusRearEnd_Move53, JusFrontStart_Move5113, JusFrontEnd_Move53, 0.5);

	//move back to middle of right of Q
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	//reset arms
	double JusRearStart_Move88[6] = { -6, 0.25, -4.4, openRearGripper, 40, -110 };
	double JusRearEnd_Move88[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move88[6] = { 5.8, 1.6, -4, openFrontGripper, 175, -104 };
	double JusFrontEnd_Move88[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move88, JusRearEnd_Move88, JusFrontStart_Move88, JusFrontEnd_Move88, 0.5);

	//move down
	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);
	//move up
	parent->Both_Smooth_Move(JusRearStart_Move53, JusRearEnd_Move53, JusFrontStart_Move5113, JusFrontEnd_Move53, 0.5);

	down();
	delay(timing);
	down();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 0;
}

int EtchControl::letterRdown()
{
	resetRearLeft();
	resetFrontLeft();
	down();
	delay(timing);
	down();
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing*2);
	parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[5], openRearGripper);
	delay(timing);
	parent->setPosition(parent->Front_Arm[4], 75);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);

	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	return 1;
}

int EtchControl::letterRup()
{
	resetRearLeft();
	resetFrontRight();
	up();
	delay(timing);
	up();
	delay(timing);
	down();
	delay(timing);
	down();
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing*2);
	parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[5], openRearGripper);
	delay(timing);
	parent->setPosition(parent->Front_Arm[4], 75);
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 90);
	delay(timing);

	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	return 1;
}

int EtchControl::letterSdown()
{
	resetRearLeft();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);
	resetRearLeft();
	count = 1;
	down();
	resetRearRight();
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);
	count = 1;
	down();
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);
	resetRearLeft();

	return 0;
}

int EtchControl::letterSup()
{
	resetRearLeft();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);
	parent->setPosition(parent->Rear_Arm[4], 180);
	count = 1;
	up();
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	count = 1;
	up();
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing * 2);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);

	return 1;
}

int EtchControl::letterTdown()
{
	resetRearLeft();
	resetFrontLeft();
	// draw T

	parent->setPosition(parent->Rear_Arm[4], 110);
	delay(timing);

	down();
	delay(timing);
	down();
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 0;
}

int EtchControl::letterTup()
{
	resetRearLeft();
	resetFrontRight();
	// draw T
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing * 2);

	parent->setPosition(parent->Rear_Arm[4], 110);
	delay(timing);

	up();
	delay(timing);
	up();
	delay(timing);

	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	return 1;
}

int EtchControl::letterUdown()
{
	resetRearLeft();
	resetFrontLeft();
	down();
	delay(timing);
	down();
	delay(timing);
	up();
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	down();
	delay(timing);
	down();
	delay(timing);

	return 0;
}

int EtchControl::letterUup()
{
	resetRearLeft();
	resetFrontLeft();

	up();
	delay(timing);
	up();
	delay(timing);
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);
	down();
	delay(timing);
	down();
	delay(timing);

	return 0;
}



int EtchControl::letterVdown()
{
	//move to top of V
	resetFrontLeft();
	resetRearRight();
	double JusRearStart_Move53[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusRearEnd_Move53[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move5113[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move53[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move53, JusRearEnd_Move53, JusFrontStart_Move5113, JusFrontEnd_Move53, 0.5);

	//reset arms
	double JusRearStart_Move88[6] = { -6, 0.25, -4.4, openRearGripper, 90, -110 };
	double JusRearEnd_Move88[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusFrontStart_Move88[6] = { 5.8, 1.6, -4, openFrontGripper, 75, -104 };
	double JusFrontEnd_Move88[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move88, JusRearEnd_Move88, JusFrontStart_Move88, JusFrontEnd_Move88, 0.5);

	//move to top of V
	parent->Both_Smooth_Move(JusRearStart_Move53, JusRearEnd_Move53, JusFrontStart_Move5113, JusFrontEnd_Move53, 0.5);

	//move back to middle of right of V
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 40, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	//reset arms
	double JusRearStart_Move889[6] = { -6, 0.25, -4.4, openRearGripper, 40, -110 };
	double JusRearEnd_Move889[6] = { -6, 0.25, -4.4, closeRearGripper, 90, -110 };
	double JusFrontStart_Move889[6] = { 5.8, 1.6, -4, openFrontGripper, 175, -104 };
	double JusFrontEnd_Move889[6] = { 5.8, 1.6, -4, closeFrontGripper, 75, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move889, JusRearEnd_Move889, JusFrontStart_Move889, JusFrontEnd_Move889, 0.5);

	//finish first side of V
	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	//start next side of V
	resetRearLeft();
	resetFrontLeft();

	//make first leg of trip
	double JusRearStart_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4, closeFrontGripper, 59, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);
	//reset arms
	double JusRearStart_Move51[6] = { -6, 0.25, -4.4, openRearGripper, 130, -110 };
	double JusRearEnd_Move51[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusFrontStart_Move5111[6] = { 5.8, 1.6, -4, openFrontGripper, 59, -104 };
	double JusFrontEnd_Move51[6] = { 5.8, 1.6, -4, closeFrontGripper, 155, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move51, JusRearEnd_Move51, JusFrontStart_Move5111, JusFrontEnd_Move51, 0.5);
	//finish
	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);

	return 0;

}

int EtchControl::letterVup()
{
	resetRearLeft();
	resetFrontRight();
	//move back to middle of right of V
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 7, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 117, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	//reset arms
	double JusRearStart_Move889[6] = { -6, 0.25, -4.4, openRearGripper, 130, -110 };
	double JusRearEnd_Move889[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusFrontStart_Move889[6] = { 5.8, 1.6, -4, openFrontGripper, 117, -104 };
	double JusFrontEnd_Move889[6] = { 5.8, 1.6, -4, closeFrontGripper, 7, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move889, JusRearEnd_Move889, JusFrontStart_Move889, JusFrontEnd_Move889, 0.5);

	//finish first side of V
	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);

	//start next side of V
	resetRearLeft();
	resetFrontLeft();

	//make first leg of trip
	double JusRearStart_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4, closeFrontGripper, 175, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4, closeFrontGripper, 59, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);
	//reset arms
	double JusRearStart_Move51[6] = { -6, 0.25, -4.4, openRearGripper, 130, -110 };
	double JusRearEnd_Move51[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusFrontStart_Move5111[6] = { 5.8, 1.6, -4, openFrontGripper, 59, -104 };
	double JusFrontEnd_Move51[6] = { 5.8, 1.6, -4, closeFrontGripper, 155, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move51, JusRearEnd_Move51, JusFrontStart_Move5111, JusFrontEnd_Move51, 0.5);
	//finish
	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.5);


	return 0;
}

int EtchControl::letterWup()
{
	letterVup();
	letterVup();
	return 0;
}

int EtchControl::letterWdown()
{
	letterVdown();
	letterVup();
	return 0;
}



void EtchControl::makeSpace()
{
	// new letter

	resetRearLeft();

	// Scroll over
	parent->setPosition(parent->Rear_Arm[4], 110);
	delay(timing);

	resetRearLeft();

	// Scroll over
	parent->setPosition(parent->Rear_Arm[4], 110);
	delay(timing);

	resetRearLeft();

}





void EtchControl::down()
{
	int rotate = 180;
	if (count == 1)
	{
		rotate = 120;
	}


	// Vertical line
	// Release knob
	parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(Clawtiming);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], rotate);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], closeFrontGripper);
	delay(Clawtiming);

	// Scroll over
	parent->setPosition(parent->Front_Arm[4], 7);
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
	delay(Clawtiming);

	// Scroll over
	parent->setPosition(parent->Front_Arm[4], 7);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], closeFrontGripper);
	delay(Clawtiming);


}
void EtchControl::resetRearLeft()
{
	// Release knob
	parent->setPosition(parent->Rear_Arm[5], openRearGripper);
	delay(Clawtiming);

	// Rotate wrist
	parent->setPosition(parent->Rear_Arm[4], 180);
	delay(timing + 50);

	// Grab knob
	parent->setPosition(parent->Rear_Arm[5], closeRearGripper);
	delay(Clawtiming);

}

void EtchControl::resetRearRight()
{
	// Release knob
	parent->setPosition(parent->Rear_Arm[5], openRearGripper);
	delay(Clawtiming);

	// Rotate wrist
	parent->setPosition(parent->Rear_Arm[4], 40);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Rear_Arm[5], closeRearGripper);
	delay(Clawtiming);

}

void EtchControl::resetFrontRight()
{

	// Release knob
	parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(Clawtiming);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], 0);
	delay(timing);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], closeFrontGripper);
	delay(Clawtiming);

}

void EtchControl::resetFrontLeft()
{

	// Release knob
	parent->setPosition(parent->Front_Arm[5], openFrontGripper);
	delay(Clawtiming);

	// Rotate wrist
	parent->setPosition(parent->Front_Arm[4], 175);
	delay(timing + 50);

	// Grab knob
	parent->setPosition(parent->Front_Arm[5], closeFrontGripper);
	delay(Clawtiming);

}

void EtchControl::diagonalUpLtR()
{
	resetRearLeft();
	resetFrontRight();
	//move down the cross part
	double JusRearStart_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusRearEnd_Move531[6] = { -6, 0.25, -4.4, closeRearGripper, 130, -110 };
	double JusFrontStart_Move51131[6] = { 5.8, 1.6, -4, closeFrontGripper, 14, -104 };
	double JusFrontEnd_Move531[6] = { 5.8, 1.6, -4, closeFrontGripper, 112, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);
	//reset arms
	double JusRearStart_Move889[6] = { -6, 0.25, -4.4, openRearGripper, 130, -110 };
	double JusRearEnd_Move889[6] = { -6, 0.25, -4.4, closeRearGripper, 180, -110 };
	double JusFrontStart_Move889[6] = { 5.8, 1.6, -4, openFrontGripper, 112, -104 };
	double JusFrontEnd_Move889[6] = { 5.8, 1.6, -4, closeFrontGripper, 14, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move889, JusRearEnd_Move889, JusFrontStart_Move889, JusFrontEnd_Move889, 0.5);
	//finish cross
	parent->Both_Smooth_Move(JusRearStart_Move531, JusRearEnd_Move531, JusFrontStart_Move51131, JusFrontEnd_Move531, 0.5);
}


void EtchControl::Pull()
{

	double TimeConstant = .4;//0.3
	double GripperSqueezeHat = 100;


	double JusRearStart_Move1[6] = { -1, 0, 2, GripperSqueezeHat, 90, -30 };
	double JusRearEnd_Move1[6] = { -8.3, 1.3, -2.5, GripperSqueezeHat, 90, -30 };
	double JusFrontStart_Move1[6] = { 1, 0, 2, 90, 90, -30 };
	double JusFrontEnd_Move1[6] = { 1, 0, 2, 90, 90, 90 };

	parent->Both_Smooth_Move(JusRearStart_Move1, JusRearEnd_Move1, JusFrontStart_Move1, JusFrontEnd_Move1, 0.3); //Move front arm out of the way and rear arm out with out

	parent->Rear_Smooth_Move(-8.3, 1.3, -2.5, GripperSqueezeHat, 90, -30, -9, 1.3, -5, GripperSqueezeHat, 87, -70, 0.2);// further down

	parent->Rear_Smooth_Move(-9, 1.3, -5, GripperSqueezeHat, 87, -70, -9, 1.3, -4.9, GripperSqueezeHat, 87, -100, TimeConstant);// wrist rotate and theta

	parent->Rear_Smooth_Move(-9, 1.3, -4.9, GripperSqueezeHat, 87, -100, -7, 1.5, -4.9, GripperSqueezeHat, 87, -110, TimeConstant); // continute rotate and theta to chassis
	delay(200);
	/*
	//set hat straight
	parent->Rear_Smooth_Move(-7, 1.5, -4.9, GripperSqueezeHat, 87, -110, -9, 1.5, -4, 110, 85, -110, TimeConstant); //move away

	parent->Rear_Smooth_Move(-9, 1.5, -4, GripperSqueezeHat, 85, -110, -9, 1.5, -5.6, GripperSqueezeHat, 85, -110, TimeConstant); //set hat

	parent->Rear_Smooth_Move(-9, 1.5, -5.6, GripperSqueezeHat, 85, -110, -8, 1.5, 0, GripperSqueezeHat, 90, -110, TimeConstant); // move away from etch
	*/
	//uncommented above so added this
	parent->Rear_Smooth_Move(-7, 1.5, -4.9, GripperSqueezeHat, 87, -110, -8, 1.5, 0, GripperSqueezeHat, 90, -110, 0.2);

	double JusRearStart_Move2[6] = { -8, 1.5, 0, GripperSqueezeHat, 90, -110 };
	double JusRearEnd_Move2[6] = { -1, 0, 2, GripperSqueezeHat, 90, -30 };
	double JusFrontStart_Move2[6] = { 1, 0, 2, 90, 90, 90 };
	double JusFrontEnd_Move2[6] = { 1, 0, 2, 90, 90, -30 };

	parent->Both_Smooth_Move(JusRearStart_Move2, JusRearEnd_Move2, JusFrontStart_Move2, JusFrontEnd_Move2, 0.2);

	//return hat and come back

	parent->RearFlipToLeft();

	parent->RearHomeLeft();

	parent->Front_Smooth_Move(1, 0, 2, 90, 90, -30, 4, 0, 0, 90, 90, -90, 0.1); // move front arm out of the way

	parent->Rear_Smooth_Move(1, 0, 2, GripperSqueezeHat, 90, -30, 4.5, 2.2, -2.5, GripperSqueezeHat, 113, -110, 0.7); //drop hat down to right above the tabs

	delay(200);
	parent->Rear_Smooth_Move(4.5, 2.2, -2.5, GripperSqueezeHat, 113, -111, 4.2, 2.1, -2.9, GripperSqueezeHat, 113, -110, 0.5); //drop hat down into tabs
	delay(200);
	parent->Rear_Smooth_Move(3.8, 2.1, -3.1, GripperSqueezeHat, 113, -105, 3.8, 2.1, -3.1, 0, 113, -105, 0.3); // hat leggo
	delay(200);
	parent->Rear_Smooth_Move(3.8, 2.1, -3.1, 0, 113, -105, 3.8, 2.3, 0, 0, 120, -105, 0.5); //move up

	double JusRearStart_Move4[6] = { 3.8, 2.5, 0, 0, 120, -105 };
	double JusRearEnd_Move4[6] = { 1, 0, 2, 110, 90, -30 };
	double JusFrontStart_Move4[6] = { 4, 0, 0, 90, 90, -90 };
	double JusFrontEnd_Move4[6] = { 1, 0, 2, 90, 90, -30 };

	parent->Both_Smooth_Move(JusRearStart_Move4, JusRearEnd_Move4, JusFrontStart_Move4, JusFrontEnd_Move4, 0.2);

	parent->RearFlipToRight();

	parent->RearHomeRight();



}


void EtchControl::Grasp()
{

	double TimeConstant = .6;//0.8;


	double savA[6] = { -1, 0, 2, 90, 90, -30 };
	double savB[6] = { -6, 0, -3, 50, 90, -110 };
	double savM[6] = { 1, 0, 2, 90, 90, -30 };
	double savN[6] = { 5.5, 1.55, -3, 90, 90, -100 };


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
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4, 40, 14, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4, closeFrontGripper, 14, -104 };


	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.1);


}

void EtchControl::Release()
{
	double TimeConstant = .3; //0.5
	// pull etch away
	double A011[6] = { -6, 0, -4.4, closeRearGripper, 30, -110 };
	double C011[6] = { -9, 0, -6, closeRearGripper, 90, -110 };
	double M011[6] = { 5.8, 1.6, -4.0, closeFrontGripper, 14, -104 };
	double N011[6] = { 8.7, 1.3, -6, closeFrontGripper, 90, -102 };
	parent->Both_Smooth_Move(A011, C011, M011, N011, TimeConstant);


	// pull etch away further
	double A012[6] = { -9, 0, -6, closeRearGripper, 90, -110 };
	double C012[6] = { -9, 0, -7, closeRearGripper, 90, -50 };
	double M012[6] = { 8.7, 1.3, -6, closeFrontGripper, 90, -102 };
	double N012[6] = { 8.7, 1.3, -7, closeFrontGripper, 90, -50 };
	parent->Both_Smooth_Move(A012, C012, M012, N012, TimeConstant);

	// release etch grip
	double A013[6] = { -9, 0, -7, closeRearGripper, 90, -50 };
	double C013[6] = { -9, 0, -7, 10, 90, -50 };
	double M013[6] = { 8.7, 1.3, -7, closeFrontGripper, 90, -50 };
	double N013[6] = { 8.7, 1.3, -7, 40, 90, -50 };
	parent->Both_Smooth_Move(A013, C013, M013, N013, 0.1);

	// Position Better for home return
	double A014[6] = { -9, 0, -7, 10, 90, -50 };
	double C014[6] = { -5, 0, 0, 10, 90, -30 };
	double M014[6] = { 8.7, 1.3, -7, 40, 90, -50 };
	double N014[6] = { 5, 1.3, 0, 40, 90, -30 };
	parent->Both_Smooth_Move(A014, C014, M014, N014, 0.2);



	//move arms to home
	double A[6] = { -5, 0, 0, 10, 90, -30 };
	double C[6] = { -1, 0, 2, 90, 90, -30 };
	double M[6] = { 5, 1.3, 0, 40, 90, -30 };
	double N[6] = { 1, 0, 2, 90, 90, -30 };
	parent->Both_Smooth_Move(A, C, M, N, 0.2);

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
	parent->Both_Smooth_Move(A001, C001, M001, N001, 0.5);
	parent->Rear_Smooth_Move(3.9, 2.2, -0.1, 20, 120, -105, 4.2, 2.2, -3.1, -5, 120, -107, TimeConstant + 0.7); //move rear arm to grab rubik hat -bend to it

	parent->Rear_Smooth_Move(4.2, 2.2, -3.1, -5, 120, -107, 4, 2.2, -3.3, 110, 120, -105, TimeConstant); //move rear arm to grab rubik hat -grasp it


	parent->Rear_Smooth_Move(4, 2.2, -3.2, 110, 120, -105, 4.1, 2.4, 0, 110, 120, -105, 0.4); //lift hat up


	parent->RearHomeLeft();
	parent->frontHomeLeft();



}

void EtchControl::ReleaseDemo()
{
	double TimeConstant = .6;//0.8;


	//Open Grippers
	double JusRearStart_Move5[6] = { -6, 0.25, -4.4, closeRearGripper, 30, -110 };
	double JusRearEnd_Move5[6] = { -6, 0.25, -4.4, 10, 30, -110 };
	double JusFrontStart_Move511[6] = { 5.8, 1.6, -4, closeFrontGripper, 14, -104 };
	double JusFrontEnd_Move5[6] = { 5.8, 1.6, -4, 40, 14, -104 };

	parent->Both_Smooth_Move(JusRearStart_Move5, JusRearEnd_Move5, JusFrontStart_Move511, JusFrontEnd_Move5, 0.1);

	// move both arms away from knobs
	double A011[6] = { -6, 0.25, -4.4, 10, 30, -110 };
	double C011[6] = { -6, 0, -3, 50, 90, -110 };
	double M011[6] = { 5.8, 1.6, -4.1, 40, 14, -104 };
	double N011[6] = { 5.5, 1.6, -3, 90, 90, -100 };

	parent->Both_Smooth_Move(A011, C011, M011, N011, TimeConstant);

	//move to home
	double savA[6] = { -6, 0, -3, 50, 90, -110  };
	double savB[6] = { -1, 0, 2, 90, 90, -30 };
	double savM[6] = { 5.5, 1.55, -3, 90, 90, -100 };
	double savN[6] = { 1, 0, 2, 90, 90, -30 };


	parent->Both_Smooth_Move(savA, savB, savM, savN, TimeConstant); 


	



	



}
