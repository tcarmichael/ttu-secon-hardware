#include "LineFollowControl.h"
#include "Mecanum.h"
#include "Wire.h"
#include "QTRSensors.h"
#include "Adafruit_MotorShield.h"
#include "ArmControl.h"
#include "Adafruit_Light_Sensor\Adafruit_TSL2561_U.h"
#include "Adafruit_Sensor\Adafruit_Sensor.h"
#include "Robot.h"
#include "ArduinoJson.h"
#include <string>
#include <stdio.h>

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

char readBuffer[200];
int readBufferIndex = 0;
int maxReadBuffer = 200;
int bracketCount = 0;

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
	//arm.frontHomeLeft();
	//arm.RearHomeLeft();
	arm.frontHomeRight();
	arm.RearHomeRight();


	/*****Robot is initialized and ready to run at this point*****/






}

void loop() {

	//{"id":"nav","m":1.0,"t":0.0,"r":0.0}
	//{"id":"etch","etchname":"Savannah"}
	while (Serial.available() > 0) {
		char c = Serial.read();

		if (readBufferIndex < maxReadBuffer - 1) {
			readBuffer[readBufferIndex++] = c;
		}

		if (c == '{') {
			bracketCount++;
		}
		else if (c == '}') {
			if (--bracketCount < 1) {
				bracketCount = 0;

				if (readBufferIndex < maxReadBuffer) {
					readBuffer[readBufferIndex++] = 0;

					Serial.println(readBuffer);
					StaticJsonBuffer<200> jsonBuffer;
					//char json[50];
					//	Serial.readBytesUntil('\n', json, 65);
					//mecanum.mecRun(.2, 0, 0);
					//
					// Step 2: Deserialize the JSON string
					//
					JsonObject& root = jsonBuffer.parseObject(readBuffer);

					if (!root.success())
					{
						Serial.println("parseObject() failed");
						return;
					}

					//
					// Step 3: Retrieve the values
					//
					const char* id = root["id"];
					Serial.println(id);
					if (strcmp(id, "nav") == 0){
						Serial.println("Inner Loop");
						double magnitude = root["m"];
						double translation = root["t"];
						double rotation = root["r"];

						mecanum.mecRun(magnitude, translation, rotation);
					}
					if (strcmp(id, "etch") == 0)
					{
						const char *name = root["etchname"];
						int count = 0;
						int DownUp = 1; //1 means call a down, 0 means calls an up letter
						int number_of_letters = strlen(name);
						Serial.println(number_of_letters);
						Serial.println(name);
						arm.Etch.Grasp();
						while (count < number_of_letters && count < 8)
						{
							//char token = *name[count];
							if (DownUp == 1)
							{
								//do down letter functions
								Serial.println(name[count]);
								Serial.println("down");
								if (toupper(name[count]) == 'A')
								{
									DownUp = arm.Etch.letterAdown();
								}
								if (toupper(name[count]) == 'B')
								{
									DownUp = arm.Etch.letterBdown();
								}
								if (toupper(name[count]) == 'C')
								{
									DownUp = arm.Etch.letterCdown();
								}
								if (toupper(name[count]) == 'D')
								{
									DownUp = arm.Etch.letterDdown();
								}
								if (toupper(name[count]) == 'E')
								{
									DownUp = arm.Etch.letterEdown();
								}
								if (toupper(name[count]) == 'F')
								{
									DownUp = arm.Etch.letterFdown();
								}
								if (toupper(name[count]) == 'G')
								{
									DownUp = arm.Etch.letterGdown();
								}
								if (toupper(name[count]) == 'H')
								{
									DownUp = arm.Etch.letterHdown();
								}
								if (toupper(name[count]) == 'I')
								{
									DownUp = arm.Etch.letterIdown();
								}
								if (toupper(name[count]) == 'J')
								{
									DownUp = arm.Etch.letterJdown();
								}
								if (toupper(name[count]) == 'K')
								{
									DownUp = arm.Etch.letterKdown();
								}
								if (toupper(name[count]) == 'L')
								{
									DownUp = arm.Etch.letterLdown();
								}
								if (toupper(name[count]) == 'M')
								{
									DownUp = arm.Etch.letterMdown();
								}
								if (toupper(name[count]) == 'N')
								{
									DownUp = arm.Etch.letterNdown();
								}
								if (toupper(name[count]) == 'O')
								{
									DownUp = arm.Etch.letterOdown();
								}
								if (toupper(name[count]) == 'P')
								{
									DownUp = arm.Etch.letterPdown();
								}
								if (toupper(name[count]) == 'Q')
								{
									DownUp = arm.Etch.letterQdown();
								}
								if (toupper(name[count]) == 'R')
								{
									DownUp = arm.Etch.letterRdown();
								}
								if (toupper(name[count]) == 'S')
								{
									DownUp = arm.Etch.letterSdown();
								}
								if (toupper(name[count]) == 'T')
								{
									DownUp = arm.Etch.letterTdown();
								}
								if (toupper(name[count]) == 'U')
								{
									DownUp = arm.Etch.letterUdown();
								}
								if (toupper(name[count]) == 'V')
								{
									DownUp = arm.Etch.letterVdown();
								}
								if (toupper(name[count]) == 'W')
								{
									DownUp = arm.Etch.letterWdown();
								}


							}
							else
							{
								//do up letters
								Serial.println(name[count]);
								Serial.println("up");
								if (toupper(name[count]) == 'A')
								{
									DownUp = arm.Etch.letterAup();
								}
								if (toupper(name[count]) == 'B')
								{
									DownUp = arm.Etch.letterBup();
								}
								if (toupper(name[count]) == 'C')
								{
									DownUp = arm.Etch.letterCup();
								}
								if (toupper(name[count]) == 'D')
								{
									DownUp = arm.Etch.letterDup();
								}
								if (toupper(name[count]) == 'E')
								{
									DownUp = arm.Etch.letterEup();
								}
								if (toupper(name[count]) == 'F')
								{
									DownUp = arm.Etch.letterFup();
								}
								if (toupper(name[count]) == 'G')
								{
									DownUp = arm.Etch.letterGup();
								}
								if (toupper(name[count]) == 'H')
								{
									DownUp = arm.Etch.letterHup();
								}
								if (toupper(name[count]) == 'I')
								{
									DownUp = arm.Etch.letterIup();
								}
								if (toupper(name[count]) == 'J')
								{
									DownUp = arm.Etch.letterJup();
								}
								if (toupper(name[count]) == 'K')
								{
									DownUp = arm.Etch.letterKup();
								}
								if (toupper(name[count]) == 'L')
								{
									DownUp = arm.Etch.letterLup();
								}
								if (toupper(name[count]) == 'M')
								{
									DownUp = arm.Etch.letterMup();
								}
								if (toupper(name[count]) == 'N')
								{
									DownUp = arm.Etch.letterNup();
								}
								if (toupper(name[count]) == 'O')
								{
									DownUp = arm.Etch.letterOup();
								}
								if (toupper(name[count]) == 'P')
								{
									DownUp = arm.Etch.letterPup();
								}
								if (toupper(name[count]) == 'Q')
								{
									DownUp = arm.Etch.letterQup();
								}
								if (toupper(name[count]) == 'R')
								{
									DownUp = arm.Etch.letterRup();
								}
								if (toupper(name[count]) == 'S')
								{
									DownUp = arm.Etch.letterSup();
								}
								if (toupper(name[count]) == 'T')
								{
									DownUp = arm.Etch.letterTup();
								}
								if (toupper(name[count]) == 'U')
								{
									DownUp = arm.Etch.letterUup();
								}
								if (toupper(name[count]) == 'V')
								{
									DownUp = arm.Etch.letterVup();
								}
								if (toupper(name[count]) == 'W')
								{
									DownUp = arm.Etch.letterWup();
								}
							}
							count++;
							arm.Etch.makeSpace();
						}
						arm.Etch.ReleaseDemo();

					}


					readBufferIndex = 0;
					break;
				}
			}

			readBufferIndex = 0;
		}
	}
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
	/*mecanum.mecRun(1.0, 0, 0);
	delay(1000);
	mecanum.mecRun(0, 0, 0);*/
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
	const double NAVIGATION_SPEED = 0.6;
	const unsigned long BACKUP_DELAY = 200;

	lineFollowerControl.set_speed(NAVIGATION_SPEED);

	// Follow the main path until it detects a branch
	int detected_branch = lineFollowerControl.SearchForBranch(LineFollowControl::LEFT, LineFollowControl::RIGHT);

	// Backup and center on branch
	mecanum.mecRun(-0.5, 0, 0);
	while (!lineFollowerControl.IsCenteredOnLine(detected_branch, false));
	mecanum.mecRun(0, 0, 0);

	// Green LED is on when going down a branch
	leds.Green_On();

	// Detect which direction to go on the branches
	double branch_rotation = ROTATION_SPEED;
	if (detected_branch == LineFollowControl::LEFT)
	{
		branch_rotation *= -1;
		leds.Blue_On();
	} else if (detected_branch == LineFollowControl::RIGHT)
	{
		branch_rotation *= 1;
		leds.White_On();
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

	// Small backup
	// Just in case we immediately run into the main branch
	mecanum.mecRun(-0.5, 0, 0);
	delay(100);
	mecanum.mecRun(0, 0, 0);

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

	// Green LED is off on main branch
	leds.Green_Off();
	leds.White_Off();
	leds.Blue_Off();

	// Go forward to move past previously taken branch
	mecanum.mecRun(NAVIGATION_SPEED, 0, 0);
	while (!lineFollowerControl.IsCenterOffLine(detected_branch));
	mecanum.mecRun(0, 0, 0);
}
