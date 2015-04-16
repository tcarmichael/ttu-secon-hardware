#include "ArmControl.h"
#include "Robot.h"

char temp[4] = {'b','r','g','y'};

int pinYellow = 4;
int pinRed = 5;
int pinBlue = 6;
int pinGreen = 7;

void SimonControl::Play()
{
	//LEDControl_Simon.Orange_Off();
	//LEDControl_Simon.Red_Off();
	//LEDControl_Simon.White_Off();
	//LEDControl_Simon.Blue_Off();
	//LEDControl_Simon.Green_Off();
	Grab();
	Simon_Play();
	Release();
	//LEDControl_Simon.Orange_Off();
	//LEDControl_Simon.Red_Off();
	//LEDControl_Simon.White_Off();
	//LEDControl_Simon.Blue_Off();
	//LEDControl_Simon.Green_Off();
}

void SimonControl::Simon_Play()
{



	//hit start forcibly
	parent->frontArm(-4.6, 1.5, -4, 180, 70, -95);
	
	/*delay(2000);
	press_red(15000);
	delay(2000);
	press_blue(15000);
	delay(2000);
	press_yellow(15000);
	delay(2000);
	press_green(15000);
	delay(2000);

	delay(5000);*/
	

	unsigned long start_time = millis();
	unsigned long end_time = start_time + 15000UL; 
	int sequence[MAX_SEQUENCE];
	int current = 0;
	bool start = true;

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
		Serial.println("Waiting for color");

		for (int i = 0; i <= current; i++)
		{
			unsigned long start_wait = millis();
			unsigned long end_wait = start_wait + 6000UL;
			unsigned long first_time = end_wait - 4000UL;
			unsigned long three_sec = start_wait + 3000UL;

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
				if (start)
				{
					if (millis() > first_time)
					{
						curr_color = 3;
					}
				}


			} while (curr_color == 0);
			sequence[i] = curr_color;
			start = false;
		}
		

		if (millis() > end_time)
		{
			break;
		}


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
		leds.Red_Off();
		leds.Blue_Off();
		leds.Green_Off();
		leds.Orange_Off();

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
	
	leds.Red_Off();
		leds.Blue_Off();
		leds.Green_Off();
		leds.Orange_Off();
}

void SimonControl::play_sequence(int curr, int sequence[], unsigned long end_t)
{
	for (int i = 0; i <= curr; i++) {
		//delay(1000);
		if (millis() > end_t)
		{
			break;
		}
		parent->frontArm(-4, 1.5, -3.2, 180, 70, -70);
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
	
	/*
	// Shorten the delay and check for the end of time more often
	for (int z = 0; z < 14; z++)
	{
		delay(250);
		if (millis() > end_t)
		{
			return;
		}
	}
	*/

	parent->Front_Smooth_Move(-4, 1.5, -3.4, 180, 70, -70, -3.2, 1.3, -3.1, 180, 70, -70, TimeConstant); // from start to hover over red
	parent->Front_Smooth_Move(-3.2, 1.3, -3.1, 180, 70, -70, -3.1, 1.4, -3.6, 150, 65, -70, 0.2); // changed from TimeConstant to 0.2 // hit red

	move_down(-3.1, 1.4, -3.6, 150, 70, -70, end_t);
	parent->frontArm(-3.2, 1.3, -3.1, 180, 70, -70); //hover over red
	

}

void SimonControl::press_blue(unsigned long end_t)
{
	Serial.print("BLUE ");
	
	/*
	// Shorten the delay and check for the end of time more often
	for (int z = 0; z < 12; z++)
	{
		delay(250);
		if (millis() > end_t)
		{
			return;
		}
	}
	*/

	parent->Front_Smooth_Move(-4, 1.5, -3.4, 180, 70, -70, -4.3, 1.7, -3.6, 120, 90, -75, TimeConstant); // from start to hover over blue
	parent->Front_Smooth_Move(-4.3, 1.7, -3.6, 120, 90, -75, -4.35, 1.4, -4, 120, 110, -75, 0.29); // hit blue
	// keep going down on z direction
	move_down(-4.2, 1.4, -4, 120, 110, -75, end_t);
	parent->frontArm(-4.2, 1.6, -3.6, 180, 70, -75); // hover over blue

}

void SimonControl::press_yellow(unsigned long end_t) {
	Serial.print("YELLOW ");
	
	/*
	// Shorten the delay and check for the end of time more often
	for (int z = 0; z < 12; z++)
	{
		delay(250);
		if (millis() > end_t)
		{
			return;
		}
	}
	*/

	parent->Front_Smooth_Move(-4, 1.5, -3.4, 180, 70, -70, -4.5, 1.2, -3.3, 160, 70, -70, TimeConstant); // from start to hover over yellow
	parent->Front_Smooth_Move(-4.5, 1.25, -3.3, 160, 70, -70, -4.48, 1.25, -4.28, 160, 70, -74, 0.4); // hit yellow

	// keep going down on z direction
	move_down(-4.48, 1.3, -4.28, 160, 70, -74, end_t);
	parent->frontArm(-4.45, 1.2, -3.5, 160, 70, -73.5); //hover over yellow
}

void SimonControl::press_green(unsigned long end_t)
{
	Serial.print("GREEN ");
	
	/*
	// Shorten the delay and check for the end of time more often
	for (int z = 0; z < 15; z++)
	{
		delay(250);
		if (millis() > end_t)
		{
			return;
		}
	}
	*/

	parent->Front_Smooth_Move(-4, 1.5, -3.4, 180, 70, -70, -4.3, 1.3, -3.6, 120, 90, -76, TimeConstant); // from start to hover over green
	parent->Front_Smooth_Move(-4.3, 1.3, -3.6, 120, 90, -76, -4.2, 1.3, -4, 120, 60, -77, 0.2); // David changed TimeConstant to 0.2 // hit green
	// keep going down on z direction
	move_down(-4.2, 1.3, -4, 120, 60, -77, end_t);
	parent->frontArm(-3.8, 0.8, -3.3, 180, 70, -75); //hover over green
}

void SimonControl::move_down(double x, double y, double z, signed int g, signed int r, signed int a, unsigned long end_t)
{
	int s = millis();
	int color;
	do
	{
		//This makes it plays faster and plays one more sequence and plays about 2 seconds longer
		color = get_color(); 
		if (color != 0)
			break;

		if (g == 150) // gripper for red
		{
			parent->Front_Smooth_Move(x, y, z, g, r, a, x - 0.02, y, z - 0.05, g, r, a, 0.2); // changed from 0.4 to 0.2
			//color = get_color();
			x = x - 0.02;
			z = z - 0.05;
		}

		// david added else if
		else if (g == 180) // gripper for green
		{
			parent->Front_Smooth_Move(x, y, z, g, r, a, x - 0.02, y, z - 0.05, g, r, a, 0.2); // changed from 0.4 to 0.2
			//color = get_color();
			x = x - 0.02;
			z = z - 0.05;
		}

		else{
			parent->Front_Smooth_Move(x, y, z, g, r, a, x, y, z - 0.05, g, r, a, 0.4);
			//color = get_color();
			z = z - 0.05;
		}

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


	// 1000 means really colored, 1 means almost nada, 0 means absolutely nothing
	if (redValue > 750)
	{
		//Serial.print("RED");
		color = 1;
		leds.Red_On();
		//LEDControl_Simon.Red_On(); // Turn on the Red LED on the LED bar
	}
	else if (blueValue > 750)
	{
		//Serial.print("BLUE");
		color = 2;
		leds.Blue_On();
		//LEDControl_Simon.Blue_On(); // Turn on the Blue LED on the LED bar
	}

	else if (yellowValue > 550 && greenValue > 750) 
	{
		//Serial.print("YELLOW");
		color = 3;
		leds.Orange_On();
		//LEDControl_Simon.Orange_On(); // Turn on the Orange LED on the LED bar
	}
	else if (greenValue > 750) 
	{
		//Serial.print("GREEN");
		color = 4;
		leds.Green_On();
		//LEDControl_Simon.Green_On(); // Turn on the Green LED on the LED bar
	}

	return color;
}

void SimonControl::Grab()
{

	double TimeConstant = .5;
	double GripConstant = 100;

	// Forcing simon to center position
	// move both arms out
	double A011[6] = { 1, 0, 2, GripConstant, 90, -30 }; //change this 4.1, 2.5, 0, GripConstant, 120, -105  savannah
	double C011[6] = { 8, 0, 0, GripConstant, 90, -105 };
	double M011[6] = { -1, 0, 2, 90, 90, -30 };
	double N011[6] = { -8.5, 0, 0, 0, 163, -30 }; //-105 to -30
	parent->Both_Smooth_Move(A011, C011, M011, N011, 0.4);

	// move both arms down
	double A01[6] = { 8, 0, 0, GripConstant, 90, -105 };
	double C01[6] = { 8.5, 0, -4.4, GripConstant, 92, -105 };
	double M01[6] = { -8.5, 0, 0, 0, 180, -105 };
	double N01[6] = { -8.5, 0, -5.6, 0, 180, -87 };// Justin altered angle to try and fix the simon squezze from squeezing the toy out
	parent->Both_Smooth_Move(A01, C01, M01, N01, 0.4);

	// Squeeze together
	double A[6] = { 8.5, 0, -4.4, GripConstant, 92, -105 };
	double B[6] = { 8.5, 1.6, -4.4, GripConstant, 92, -105 };
	double M[6] = { -8.5, 0, -5.6, 0, 180, -87 };
	double N[6] = { -8.5, .5, -5.6, 0, 180, -87 };


	parent->Both_Smooth_Move(A, B, M, N, 0.4);

	// Pull out
	double A2[6] = { 8.5, 1.7, -4.4, GripConstant, 92, -105 };
	double B2[6] = { 8.5, 0, -4.4, GripConstant, 92, -105 };
	double M2[6] = { -8.5, .5, -5.6, 0, 180, -87 };
	double N2[6] = { -9, 0, -5, 0, 180, -87 }; //105


	parent->Both_Smooth_Move(A2, B2, M2, N2, 0.3);
	// Pull in setup
	double A3[6] = { 8.5, 0, -4.4, GripConstant, 92, -105 };
	double B3[6] = { 7.5, -1, -5, GripConstant, 92, -105 };
	double M3[6] = { -9, 0, -4.3, 0, 163, -87 };
	double N3[6] = { -9, 0, -4.5, 0, 163, -50 };


	parent->Both_Smooth_Move(A3, B3, M3, N3, 0.3);
	// Pull in setup step 2
	parent->Front_Smooth_Move(-9, 0, -4.5, 0, 163, -50, -9, 2, -5, 0, 80, -50, TimeConstant);

	// pull in wrist swing down
	parent->Front_Smooth_Move(-9, 2, -5, 0, 80, -50, -9.2, 2, -5.2, 50, 80, -90, TimeConstant);

	// pull in x direction 
	parent->Front_Smooth_Move(-9.2, 2, -5.2, 0, 80, -90, -6, 2, -5.75, 50, 80, -110, TimeConstant);

	//move front arm out of the way
	parent->Front_Smooth_Move(-6, 2, -5.5, 50, 80, -110, -7, 2, -5, 50, 80, -90, 0.3); //move back
	parent->Front_Smooth_Move(-7, 2, -5, 50, 80, -90, -4, 1.5, -3.8, 180, 70, -70, TimeConstant); // move above start button

	//move rear arm to hold simon
	parent->Rear_Smooth_Move(7.5, -1, -5, GripConstant, 92, -105, 8.5, -0.5, -5, GripConstant, 95, -105, 0.4); // move out in x 8.5, 0, -5, GripConstant, 95, -105
	parent->Rear_Smooth_Move(8.5, -0.5, -5, GripConstant, 95, -105, 8.6, 2.8, -5, GripConstant, 100, -105, 0.4); // move in front of simon in y 8.6, 2.5, -5, GripConstant, 100, -105,
	parent->Rear_Smooth_Move(8.6, 2.8, -5, GripConstant, 100, -105, 8.5, 2.35, -5, GripConstant, 100, -115, 0.4); //hold simon 7.3, 3, -5, GripConstant, 100, -105

}

void SimonControl::Release()
{
	double TimeConstant = .5;
	double GripConstant = 100;
	//take hat to skid and move front arm home

	parent->Rear_Smooth_Move(7, 2, -5, GripConstant, 130, -105, 7, 0, -5, GripConstant, 130, -105, TimeConstant);
	parent->Front_Smooth_Move(-4, 1.5, -3.3, 180, 70, -70, -4, 0, -2, 180, 70, -70, TimeConstant);	

	double A001[6] = { 7, 0, -5, GripConstant, 130, -105 };
	double C001[6] = { 1, 0, 2, 90, 90, -30 };
	double M001[6] = { -4, 0, -2, 180, 70, -70, };
	double N001[6] = { -1, 0, 2, 90, 90, -30 }; //push simon out
	parent->Both_Smooth_Move(A001, C001, M001, N001, TimeConstant);


	parent->FrontFlipToRight();
	parent->frontHomeRight();
	parent->RearFlipToRight();
	parent->RearHomeRight();
	
}
