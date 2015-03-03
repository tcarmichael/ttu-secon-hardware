#include "ArmControl.h"

char temp[4] = {'b','r','g','y'};

int pinYellow = 4;
int pinRed = 5;
int pinBlue = 6;
int pinGreen = 7;




void SimonControl::Simon_Play()
{
	Grab();
	Play();
	Release();
}

void SimonControl::Play()
{

	//hit start forcibly
	parent->frontArm(-4.6, 1.5, -3.95, 180, 70, -95);
	
	//delay(2000);
	//press_red();
	//delay(2000);
	//press_blue();
	//delay(2000);
	//press_yellow();
	//delay(2000);
	//press_green();
	//delay(2000);

	//delay(5000);
	

	unsigned long start_time = millis();
	unsigned long end_time = start_time + 15000UL;
	int sequence[MAX_SEQUENCE];
	int current = 0;

	pinMode(pinYellow, INPUT);
	pinMode(pinRed, INPUT);
	pinMode(pinBlue, INPUT);
	pinMode(pinGreen, INPUT);

	//double current_time = start_time;
	Serial.println("timing");
	// Serial.println(current_time - start_time);
	
	while (millis() <= end_time)
	{
		int curr_color;
		// Wait for Simon sequence
		// Serial.println("Waiting for Simon");
		Serial.println("Waiiting for color");

		for (int i = 0; i <= current; i++)
		{
			unsigned long start_wait = millis();
			unsigned long end_wait = start_wait + 6000UL;
			do
			{
				delay(100); // delay to get the timing between each sequence
				if (millis() > end_time)
				{
					break;
				}
				if (millis() > end_wait) // if the robot does not hear a tone after 6 seconds, assume DONE
				{
					goto DONE;
				}
				// Wait until a tone is detected
				curr_color = get_color();

			} while (curr_color == 0);
			sequence[i] = curr_color;
		}
		
/*		do
		{
			delay(100); // delay to get the timing between each sequence

			if (millis() > end_time)
			{
				break;
			}

			// Wait until a tone is detected
			curr_color = get_color();

		} while (curr_color == 0);

		if (millis() > end_time)
		{
			break;
		}

		for (int i = 0; i < current; i++)
		{
			// Ignore color
			get_color();

			if (millis() > end_time)
			{
				break;
			}
		}

		sequence[current] = curr_color;
*/
		if (millis() > end_time)
		{
			break;
		}

		/*for (int j = 0; j <= current; j++)
		{
			Serial.print(sequence[j]);
			Serial.print(" ");

			if (millis() > end_time)
			{
				break;
			}
		}*/

		//play_sequence(current, sequence);
		Serial.println();

		// Wait for user sequence
		Serial.println("Wait for user");
//		for (int i = 0; i < current + 1; i++)
//		{
		if (millis() > end_time)
		{
			break;
		}

		play_sequence(current, sequence, end_time);
		delay(500); // delay needed after the arm plays a sequence
		//get_color();
//		}

		Serial.println();

		// Serial.println(current);
		// current_time = millis();
		current++;
		//Serial.println("timing");
		//Serial.println(current_time - start_time);
	}

DONE:
	Serial.println(start_time);
	Serial.println(millis());
	
	
}

void SimonControl::play_sequence(int curr, int sequence[], unsigned long end_t)
{
	for (int i = 0; i <= curr; i++) {
		//delay(1000);
		if (millis() > end_t)
		{
			break;
		}
		parent->frontArm(-4, 1.5, -3.4, 180, 70, -70);
		switch (sequence[i]) {
		case 1:
			press_red(end_t);
			break;
		case 2:
			press_blue(end_t);
			break;
		case 3:
			press_yellow(end_t);
			break;
		case 4:
			press_green(end_t);
			break;
		}
	}
}

void SimonControl::press_red(unsigned long end_t)
{
	Serial.print("RED ");
	parent->Front_Smooth_Move(-4, 1.5, -3.4, 180, 70, -70, -3.2, 1.3, -3.1, 180, 70, -70, TimeConstant); // from start to hover over red
	parent->Front_Smooth_Move(-3.2, 1.3, -3.1, 180, 70, -70, -3.1, 1.4, -3.5, 180, 70, -70, TimeConstant); // hit red
	//add error function here
	move_down(-3.1, 1.4, -3.5, 180, 70, -70, end_t);
	parent->frontArm(-3.2, 1.3, -3.1, 180, 70, -70); //hover over red
	//parent->Front_Smooth_Move(-3.2, 1.4, -3.8, 180, 70, -70, -3.2, 1.3, -3.1, 180, 70, -70, TimeConstant); // hover over red
	// dont uncomment  //parent->Front_Smooth_Move(-3.2, 1.3, -3.1, 180, 70, -70, -4, 1.5, -3.7, 180, 70, -70, TimeConstant); // from red to start (x,y,z,g,r,theta,x2,y2,z2,g2,r2,theta2)
}

void SimonControl::press_blue(unsigned long end_t)
{
	Serial.print("BLUE ");
	parent->Front_Smooth_Move(-4, 1.5, -3.4, 180, 70, -70, -4.2, 1.6, -3.6, 120, 90, -75, TimeConstant); // from start to hover over blue
	parent->Front_Smooth_Move(-4.2, 1.6, -3.6, 120, 90, -75, -4.2, 1.4, -3.9, 120, 110, -75, TimeConstant); // hit blue
	// keep going down on z direction
	move_down(-4.2, 1.4, -3.9, 120, 110, -75, end_t);
	parent->frontArm(-4.2, 1.6, -3.6, 180, 70, -75); // hover over blue
	//parent->Front_Smooth_Move(-4, 1.4, -4.2, 120, 110, -75, -4.2, 1.6, -3.6, 180, 70, -75, TimeConstant); // hover over blue
	// dont uncomment//parent->Front_Smooth_Move(-4.2, 1.5, -3.6, 180, 70, -75, -4, 1.5, -3.7, 180, 70, -70, TimeConstant); // from blue to start
}

void SimonControl::press_yellow(unsigned long end_t) {
	Serial.print("YELLOW ");
	parent->Front_Smooth_Move(-4, 1.5, -3.4, 180, 70, -70, -4.2, 1.3, -3.7, 160, 70, -70, TimeConstant); // from start to hover over yellow
	parent->Front_Smooth_Move(-4.2, 1.3, -3.7, 160, 70, -70, -4, 0.8, -4.1, 160, 70, -70, TimeConstant); // hit yellow
	// keep going down on z direction
	move_down(-4, 0.8, -4.2, 160, 70, -70, end_t);
	parent->frontArm(-4.5, 1.3, -3.7, 180, 70, -70); //hover over yellow
	//parent->Front_Smooth_Move(-4.2, 0.8, -4.1, 180, 70, -70, -4.5, 1.3, -3.7, 180, 70, -70, TimeConstant); // hover over yellow
	// dont uncomment//parent->Front_Smooth_Move(-4.5, 1.3, -3.7, 180, 70, -70, -4, 1.5, -3.7, 180, 70, -70, TimeConstant); // from yellow to start
}

void SimonControl::press_green(unsigned long end_t)
{
	Serial.print("GREEN ");
	parent->Front_Smooth_Move(-4, 1.5, -3.4, 180, 70, -70, -3.8, 0.8, -3.3, 180, 70, -75, TimeConstant); // from start to hover over green
	parent->Front_Smooth_Move(-3.8, 0.8, -3.3, 180, 70, -75, -3.8, 0.75, -3.75, 180, 70, -75, TimeConstant); // hit green
	// keep going down on z direction
	move_down(-3.8, 0.75, -3.75, 180, 70, -75, end_t);
	parent->frontArm(-3.8, 0.8, -3.3, 180, 70, -75); //hover over green
	//parent->Front_Smooth_Move(-3.8, 0.8, -3.5, 180, 70, -75, -3.8, 0.8, -3.3, 180, 70, -75, TimeConstant); // hover over green
	// dont uncomment//parent->Front_Smooth_Move(-3.8, 0.8, -3.3, 180, 70, -75, -4, 1.5, -3.7, 180, 70, -70, TimeConstant);
}

void SimonControl::move_down(double x, double y, double z, signed int g, signed int r, signed int a, unsigned long end_t)
{
	int s = millis();
	int color;
	do
	{
		parent->Front_Smooth_Move(x, y, z, g, r, a, x, y, z - 0.05, g, r, a, 0.4);
		color = get_color();
		z = z - 0.05;
		if (millis() - s >= 4000 || millis() > end_t)
			color = 9;
	} while (color == 0);
}

int SimonControl::get_color()
{

	int redValue = 0, blueValue = 0, yellowValue = 0, greenValue = 0;

	for (int i = 0; i < 1000; i++) 
	{
		int _redValue = digitalRead(pinRed);
		int _blueValue = digitalRead(pinBlue);
		int _yellowValue = digitalRead(pinYellow);
		int _greenValue = digitalRead(pinGreen);

		if (_redValue == 0)
		{
			//Serial.print("RED");
			redValue++;
		}
		if (_blueValue == 0) 
		{
			//Serial.print("BLUE");
			blueValue++;
		}
		if (_yellowValue == 0)
		{
			//Serial.print("YELLOW");
			yellowValue++;
		}
		if (_greenValue == 0)
		{
			//Serial.print("GREEN");
			greenValue++;
		}

		delayMicroseconds(100);

	}


	int color = 0;
	/*Serial.print("yellow: ");
	Serial.print(yellowValue);
	Serial.print(" red: ");
	Serial.print(redValue);
	Serial.print(" blue: ");
	Serial.print(blueValue);
	Serial.print(" green: ");
	Serial.println(greenValue);*/

	// 1000 means really colored, 1 means almost nada, 0 means absolutely nothing
	if (redValue > 750)
	{
		//Serial.print("RED");
		color = 1;
	}
	else if (blueValue > 750)
	{
		//Serial.print("BLUE");
		color = 2;
	}
	//    else if (yellowValue == 0 && greenValue == 0) {
	//      //Serial.print("YELLOW");
	//      color = 3;
	//    }
	else if (yellowValue > 550 && greenValue > 750) 
	{
		//Serial.print("YELLOW");
		color = 3;
	}
	else if (greenValue > 750) 
	{
		//Serial.print("GREEN");
		color = 4;
	}

	return color;
}

void SimonControl::Grab()
{

	double TimeConstant = .5;
	parent->frontHomeLeft();
	parent->RearHomeLeft();

	/*//grab hat from skid
	double A001[6] = { 1, 0, 2, 90, 90, -30 };
	double C001[6] = { 3.9, 2.2, -0.1, 20, 120, -105 };
	double M001[6] = { -1, 0, 2, 90, 90, -30 };
	double N001[6] = { -1, 0, 2, 90, 90, 90 };
	parent->Both_Smooth_Move(A001, C001, M001, N001, TimeConstant);

	parent->Rear_Smooth_Move(3.9, 2.2, -0.1, 20, 120, -105, 4.0, 2.5, -3.1, 0, 120, -105, TimeConstant); //move rear arm to grab rubik hat -bend to it
	delay(100);
	parent->Rear_Smooth_Move(4.0, 2.5, -3.1, 0, 120, -105, 4.0, 2.5, -3.1, 110, 120, -105, TimeConstant); //move rear arm to grab rubik hat -grasp it
	delay(100);
	parent->Rear_Smooth_Move(4.1, 2.5, -3.1, 110, 120, -105, 4.1, 2.5, 0, 110, 120, -105, TimeConstant); //lift hat up
	delay(100);*/

	// Forcing simon to center position
	// move both arms out
	double A011[6] = { 1, 0, 2, 110, 90, -30 }; //change this 4.1, 2.5, 0, 110, 120, -105  savannah
	double C011[6] = { 8, 0, 0, 110, 90, -105 };
	double M011[6] = { -1, 0, 2, 90, 90, -30 };
	double N011[6] = { -9, 0, 0, 0, 163, -30 }; //-105 to -30
	parent->Both_Smooth_Move(A011, C011, M011, N011, TimeConstant);
	delay(100);

	// move both arms down
	double A01[6] = { 8, 0, 0, 110, 90, -105 };
	double C01[6] = { 8, 0, -4.3, 110, 90, -105 };
	double M01[6] = { -9, 0, 0, 0, 180, -105 };
	double N01[6] = { -9, 0, -5.6, 0, 180, -105 };
	parent->Both_Smooth_Move(A01, C01, M01, N01, TimeConstant);
	delay(100);

	// Squeeze together
	double A[6] = { 8.5, 0, -4.3, 110, 92, -105 };
	double B[6] = { 8.5, 1.6, -4.3, 110, 92, -105 };
	double M[6] = { -8.5, 0, -5.6, 0, 180, -105 };
	double N[6] = { -8.5, .7, -5.6, 0, 180, -105 };


	parent->Both_Smooth_Move(A, B, M, N, TimeConstant);
	delay(100);

	// Pull out
	double A2[6] = { 8.5, 1.7, -4.3, 110, 92, -105 };
	double B2[6] = { 8.5, 0, -4.3, 110, 92, -105 };
	double M2[6] = { -8.5, .6, -5.6, 0, 180, -105 };
	double N2[6] = { -9, 0, -5, 0, 180, -105 };


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
	parent->Front_Smooth_Move(-9, 2, -5, 0, 80, -50, -9.2, 2, -5.2, 50, 80, -90, TimeConstant);
	delay(100);

	// pull in x direction 
	parent->Front_Smooth_Move(-9.2, 2, -5.2, 0, 80, -90, -6, 2, -5.75, 50, 80, -110, TimeConstant);
	delay(100);

	//move front arm out of the way
	parent->Front_Smooth_Move(-6, 2, -5.5, 50, 80, -110, -7, 2, -5, 50, 80, -90, TimeConstant); //move back
	delay(100);
	parent->Front_Smooth_Move(-7, 2, -5, 50, 80, -90, -4, 1.5, -3.7, 180, 70, -70, TimeConstant); // move above start button

	//move rear arm to hold simon
	parent->Rear_Smooth_Move(7.5, 0, -5, 110, 92, -105, 8.5, 0, -5, 110, 130, -105, TimeConstant); // move out in x
	delay(100);
	parent->Rear_Smooth_Move(8.5, 0, -5, 110, 130, -105, 8.5, 2, -5, 110, 130, -105, TimeConstant); // move in front of simon in y
	delay(100);
	parent->Rear_Smooth_Move(8.5, 2, -5, 110, 130, -105, 7, 2, -5, 110, 130, -105, TimeConstant); //hold simon
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


	/*parent->Rear_Smooth_Move(4.0, 2.5, -2, 110, 120, -105, 4, 2.5, -3.1, 110, 120, -105, TimeConstant); //drop hat down
	delay(100);

	parent->Rear_Smooth_Move(4, 2.5, -3.1, 110, 120, -105, 4, 2.5, -3.1, 0, 120, -105, TimeConstant); // hat leggo
	delay(100);

	parent->Rear_Smooth_Move(4, 2.5, -3.1, 110, 120, -105, 4, 2.5, 2, 0, 120, -105, TimeConstant); //move up
	delay(100);*/


	parent->RearHomeLeft();
	parent->frontHomeLeft();
	parent->FrontFlipToRight();
	parent->frontHomeRight();
	parent->RearFlipToRight();
	parent->RearHomeRight();
	
}
