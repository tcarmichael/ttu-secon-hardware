#include "LineFollowControl.h"
#include "Mecanum.h"
#include "Wire.h"
#include "QTRSensors.h"
#include "Adafruit_MotorShield.h"
#include "ArmControl.h"
#include "Adafruit_Light_Sensor\Adafruit_TSL2561_U.h"
#include "Adafruit_Sensor\Adafruit_Sensor.h"
#include "Robot.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

// Interacts with the mecanum wheels and the motor shield
Mecanum mecanum;
LineFollowControl lineFollowerControl(&mecanum);

LEDController leds;

// Controls the arm movements
ArmControl arm;

void setup() {
	Serial.begin(9600);
	// Used to initialize the LEDs :)


	//Example code Line for LEDs, just change the color word
	leds.LED_Setup();
	
	// Initialize the mecanum wheels
	Serial.println("Initializing the mecanum wheels");
	mecanum.begin();
	mecanum.mecRun(0, 0, 0);
	
	// Calibrate the line followers
	Serial.println("Calibrating");
	//lineFollowerControl.defaultCalibration();
	lineFollowerControl.DefaultCalibrationOtherSide();

	// Set the arms in position
	arm.begin();
	arm.frontHomeLeft();
	arm.RearHomeLeft();
	//arm.frontHomeRight();
	//arm.RearHomeRight();
	

	/*****Robot is initialized and ready to run at this point*****/
	//arm.Simon.Grab();
	//arm.Simon.Play();
	//arm.Etch.Pull();
	//arm.Etch.Release();
	//arm.Etch.Play();
	//arm.Rubiks.Play();
	//arm.Rubiks.Release();

	//arm.Rubiks.Play();
	//delay(15000);

	// Wait for start signal
	Serial.println("Waiting for LED");
	WaitForLed();
	leds.Blue_Off();
	leds.Green_Off();
	leds.White_Off();

	// Begin line following
	Serial.println("Starting line following");
	FollowLine();
}

void loop() {
	//arm.Rubiks.Grab();
	//arm.Rubiks.Rotate();
	//arm.Rubiks.Release();
	/*lineFollowerControl.setSide(LineFollowControl::LEFT);
	ReadSensorData();*/
	//FollowSide(LineFollowControl::RIGHT);
	//SpeedRamping();
	//MoveInSquare(true);
	//Strafe();
	

}

void WaitForLed()
{
	// Initialize the sensor
	Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
	if (!tsl.begin())
	{
		/* There was a problem detecting the ADXL345 ... check your connections */
		Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
	}

	// Configure the sensor
	tsl.enableAutoRange(true);
	tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);

	leds.Blue_On();
	leds.Green_On();
	leds.White_On();
	
	// Wait for the sensor to return a value
	sensors_event_t event;
	do {
		tsl.getEvent(&event);
	} while (!event.light);

	leds.Orange_On();
	leds.Red_On();

	do {
		do
		{
			tsl.getEvent(&event);
		} while (event.light);

		delay(1500);
		tsl.getEvent(&event);
	} while (event.light);
	
}

void FollowLine()
{
	// Follow the front line-following sensor
	lineFollowerControl.setSide(LineFollowControl::FRONT);

	// Get out of the box
	mecanum.mecRun(0.5, 0, 0);
	while (!(lineFollowerControl.IsCenterOffLine(LineFollowControl::LEFT)
	&& lineFollowerControl.IsCenterOffLine(LineFollowControl::RIGHT)));
	mecanum.mecRun(0, 0, 0);

	// Play each of the games
	FindBranch(LineFollowControl::LEFT, &arm.Simon);
	FindBranch(LineFollowControl::RIGHT, &arm.Etch);
	FindBranch(LineFollowControl::LEFT, &arm.Rubiks);
	FindBranch(LineFollowControl::RIGHT, &arm.Card);

	// Find the finish line
	lineFollowerControl.followUntilWhite();

	// Drive completely over the finish line
	mecanum.mecRun(1.0, 0, 0);
	delay(1000);
	mecanum.mecRun(0, 0, 0);
}

void Strafe()
{
	mecanum.mecRun(2.0, PI / 2, 0);
	delay(3000);
	mecanum.mecRun(2.0, 3 * PI / 2, 0);
	delay(3000);
}

void MoveInSquare(bool acceleration)
{
	double max_speed = 6;

	for (int i = 0; i < 4; i++) {
		// Accelerate
		if (acceleration)
		{
			for (double speed = 0; speed < max_speed; speed += 0.05)
			{
				mecanum.mecRun(speed, i * PI / 2, 0);
				delay(50);
			}
		}

		// Constant speed
		mecanum.mecRun(max_speed, i * PI / 2, 0);
		delay(500);

		// Decelerate
		if (acceleration)
		{
			for (double speed = max_speed; speed > 0; speed -= 0.05)
			{
				mecanum.mecRun(speed, i * PI / 2, 0);
				delay(50);
			}
		}

		// Pause between sides
		delay(100);
	}
}

void SpeedRamping() {
	for (double speed = 0; speed < 1.5; speed += 0.1) {
		mecanum.mecRun(speed, 3 * PI / 2, 0.00);
		delay(50);
	}

	mecanum.mecRun(2.0, 3 * PI / 2, 0.00);
	delay(2000);
}

void FollowSide(int side) {
	lineFollowerControl.setSide(side);
	lineFollowerControl.followInfinitely();
}

void ReadSensorData() {
	QTRSensorsRC* sensor = lineFollowerControl.getCurrentSensor();

	// Minimum
	for (int i = 0; i < 8; i++) {
		Serial.print(sensor->calibratedMinimumOn[i]);
		Serial.print(' ');
	}
	Serial.println();

	// Maximum
	for (int i = 0; i < 8; i++) {
		Serial.print(sensor->calibratedMaximumOn[i]);
		Serial.print(' ');
	}
	Serial.println();

	// Raw values
	unsigned int sensorValues[8];
	sensor->read(sensorValues, QTR_EMITTERS_ON);
	for (int i = 0; i < 8; i++) {
		Serial.print(sensorValues[i]);
		Serial.print(' ');
	}
	Serial.println();

	// Calibrated values
	int position = sensor->readLine(sensorValues, QTR_EMITTERS_ON, 1);
	for (int i = 0; i < 8; i++) {
		Serial.print(sensorValues[i]);
		Serial.print(' ');
	}
	Serial.println();

	// Position
	Serial.println(position);

	delay(1000);
}
// side - Side of the robot that operates the toy
void FindBranch(int toy_side, GameControl* game)
{
	// Navigation constants
	const double ROTATION_SPEED = 0.5;
	const double NAVIGATION_SPEED = 0.5;
	const unsigned long BACKUP_DELAY = 200;

	lineFollowerControl.set_speed(NAVIGATION_SPEED);

	// Follow the main path until it detects a branch
	int detected_branch = lineFollowerControl.SearchForBranch(LineFollowControl::LEFT, LineFollowControl::RIGHT);

	// Detect which direction to go on the branches
	double branch_rotation = ROTATION_SPEED;
	if (detected_branch == LineFollowControl::LEFT)
	{
		branch_rotation *= -1;
	} else if (detected_branch == LineFollowControl::RIGHT)
	{
		branch_rotation *= 1;
	}

	// Detect which direction to rotate to reach the toy
	double toy_rotation = ROTATION_SPEED;
	if (toy_side == LineFollowControl::LEFT)
	{
		toy_rotation *= 1;
	} else if (toy_side == LineFollowControl::RIGHT)
	{
		toy_rotation *= -1;
	}

	// Rotate to follow branch
	lineFollowerControl.RotateUntilLine(branch_rotation);

	// Follow the branch to the box
	lineFollowerControl.followUntilWhite();

	// Back up from the box
	mecanum.mecRun(-NAVIGATION_SPEED, 0, 0);
	delay(BACKUP_DELAY);
	mecanum.mecRun(0, 0, 0);
	
	// Orient on first box
	int other_sensor = -1;
	if (toy_side == LineFollowControl::LEFT)
	{
		other_sensor = LineFollowControl::RIGHT;
	} else if (toy_side == LineFollowControl::RIGHT)
	{
		other_sensor = LineFollowControl::LEFT;
	}
	lineFollowerControl.RotateUntilLine(toy_rotation, other_sensor);

	// Center on the line
	lineFollowerControl.CenterOnLine(LineFollowControl::LEFT, LineFollowControl::RIGHT);

	// Play the game
	game->Play();

	// Rotate back on the branch
	lineFollowerControl.RotateUntilLine(toy_rotation);

	// Follow the branch back to the main path
	lineFollowerControl.followUntilWhite();

	// Cross over the main branch
	bool left_cross = false;
	bool right_cross = false;

	mecanum.mecRun(NAVIGATION_SPEED, 0, 0);
	// Wait for one sensor to cross over the line
	while (!(lineFollowerControl.IsCenteredOnLine(LineFollowControl::LEFT, true)
		|| lineFollowerControl.IsCenteredOnLine(LineFollowControl::RIGHT, true)));
	mecanum.mecRun(0, 0, 0);

	// Turn back to main branch
	lineFollowerControl.RotateUntilLine(branch_rotation);

	// Go forward to move past previously taken branch
	mecanum.mecRun(NAVIGATION_SPEED, 0, 0);
	while (!lineFollowerControl.IsCenterOffLine(detected_branch));
	mecanum.mecRun(0, 0, 0);
}
