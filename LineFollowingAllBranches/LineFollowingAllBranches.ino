#include "LineFollowControl.h"
#include "Mecanum.h"
#include "Wire.h"
#include "QTRSensors.h"
#include "Adafruit_MotorShield.h"
#include "ArmControl.h"
#include "Adafruit_Light_Sensor\Adafruit_TSL2561_U.h"
#include "Adafruit_Sensor\Adafruit_Sensor.h"

// Interacts with the mecanum wheels and the motor shield
Mecanum mecanum;
LineFollowControl lineFollowerControl(&mecanum);

// Controls the arm movements
ArmControl arm;

void setup() {
	Serial.begin(9600);

	// Initialize the mecanum wheels
	Serial.println("Initializing the mecanum wheels");
	mecanum.begin();
	
	// Calibrate the line followers
	Serial.println("Calibrating");
	delay(500);
	lineFollowerControl.defaultCalibration();

	// Set the arms in position
	arm.begin();
	arm.frontHomeRight();
	arm.RearHomeRight();

	// Wait for start signal
	Serial.println("Waiting for LED");
	//WaitForLed();
	
	// Begin line following
	Serial.println("Starting line following");
	followLine();
}

void loop() {
	//ReadSensorData();
	//FollowSide();
	//SpeedRamping();
	//MoveInSquare();
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
	
	// Wait for the sensor to return a value
	sensors_event_t event;
	do {
		tsl.getEvent(&event);
	} while (!event.light);
}


void followLine()
{
	delay(1000);

	// Get out of the box
	mecanum.mecRun(1.5, 0, 0);
	delay(500);
	mecanum.mecRun(0, 0, 0);

	// Follow the front line sensor until the left line sensor finds a line
	Serial.println("Following the front line sensor");
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	lineFollowerControl.followUntilLine(LineFollowControl::LEFT);
	delay(100);

	Serial.println("Turn left 90");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);

	Serial.println("Following the left line sensor");
	lineFollowerControl.followUntilWhite();
	delay(100);

	Serial.println("Play Simon");

	/*Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(400);
	mecanum.mecRun(0, 0, 0);
	delay(100);*/
	
	lineFollowerControl.RotateUntilLine(1.0, LineFollowControl::RIGHT);
	delay(1000);

	mecanum.mecRun(1.3, 3 * PI / 2, 0);
	delay(1000);
	mecanum.mecRun(0, 0, 0);
	delay(2000);

	// Play Simon here
	//arm.Simon.Play();

	mecanum.mecRun(1.3, PI / 2, 0);
	delay(800);
	mecanum.mecRun(0, 0, 0);
	delay(2000);

	Serial.println("Turn right 180");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();
	delay(100);

	Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(400);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	Serial.println("Turn left 90");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);

	Serial.println("Wait on right line sensor");
	lineFollowerControl.followUntilLine(LineFollowControl::RIGHT);
	delay(100);

	Serial.println("Turn right 90");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();
	delay(100);

	Serial.println("Play Etch-A-Sketch");

	/*Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(400);
	mecanum.mecRun(0, 0, 0);
	delay(100);*/

	lineFollowerControl.RotateUntilLine(-1.0, LineFollowControl::LEFT);
	delay(1000);

	mecanum.mecRun(1.3, PI / 2, 0);
	delay(1000);
	mecanum.mecRun(0, 0, 0);
	delay(5000);

	// Play game here
	arm.Etch.Etch_Play();

	mecanum.mecRun(1.3, 3 * PI / 2, 0);
	delay(600);
	mecanum.mecRun(0, 0, 0);
	delay(2000);

	Serial.println("Turn left 180");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();
	delay(100);

	Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(400);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	Serial.println("Turn right 90");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(100);

	lineFollowerControl.followUntilLine(LineFollowControl::LEFT);
	delay(100);

	Serial.println("Turn left 90");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);

	Serial.println("Following the left line sensor");
	lineFollowerControl.followUntilWhite();
	delay(100);

	Serial.println("Play Rubik's Cube");

	lineFollowerControl.RotateUntilLine(1.0, LineFollowControl::RIGHT);
	delay(1000);

	mecanum.mecRun(1.3, 3 * PI / 2, 0);
	delay(1000);
	mecanum.mecRun(0, 0, 0);
	delay(2000);

	// Play Rubiks here

	mecanum.mecRun(1.3, PI / 2, 0);
	delay(600);
	mecanum.mecRun(0, 0, 0);
	delay(2000);


	/*Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(400);
	mecanum.mecRun(0, 0, 0);
	delay(100);*/

	Serial.println("Turn right 180");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();
	delay(100);

	Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(400);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	Serial.println("Turn left 90");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);

	Serial.println("Wait on right line sensor");
	lineFollowerControl.followUntilLine(LineFollowControl::RIGHT);
	delay(100);

	Serial.println("Turn right 90");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(1000);

	lineFollowerControl.followUntilWhite();
	delay(2000);

	Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(600);
	mecanum.mecRun(0, 0, 0);
	delay(5000);

	// Play game here
	arm.Card.Card_Play();

	Serial.println("Turn left almost 180");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(2000);

	lineFollowerControl.followUntilWhite();
	delay(2000);

	Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(400);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	Serial.println("Turn right 90");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();

	/*Serial.println("Following the right line sensor");
	lineFollowerControl.setSide(LineFollowControl::RIGHT);
	lineFollowerControl.followUntilLine(LineFollowControl::FRONT);
	delay(2000);

	Serial.println("Following the front line sensor");
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	lineFollowerControl.followUntilLine(LineFollowControl::RIGHT);
	delay(1000);

	Serial.println("Following the right line sensor");
	lineFollowerControl.setSide(LineFollowControl::RIGHT);
	lineFollowerControl.followUntilWhite();
	delay(1000);

	Serial.println("Following the left line sensor");
	lineFollowerControl.setSide(LineFollowControl::LEFT);
	lineFollowerControl.followUntilLine(LineFollowControl::FRONT);
	delay(1000);

	Serial.println("Following the front line sensor");
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	lineFollowerControl.followUntilLine(LineFollowControl::LEFT);
	delay(1000);

	Serial.println("Following the left line sensor");
	lineFollowerControl.setSide(LineFollowControl::LEFT);
	lineFollowerControl.followUntilWhite();
	delay(2000);

	Serial.println("Following the right line sensor");
	lineFollowerControl.setSide(LineFollowControl::RIGHT);
	lineFollowerControl.followUntilLine(LineFollowControl::FRONT);
	delay(2000);

	Serial.println("Following the front line sensor");
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	lineFollowerControl.followUntilLine(LineFollowControl::RIGHT);
	delay(1000);

	Serial.println("Following the right line sensor");
	lineFollowerControl.setSide(LineFollowControl::RIGHT);
	lineFollowerControl.followUntilWhite();
	delay(1000);

	Serial.println("Following the left line sensor");
	lineFollowerControl.setSide(LineFollowControl::LEFT);
	lineFollowerControl.followUntilLine(LineFollowControl::FRONT);
	delay(1000);*/

	Serial.println("Done");
}

void MoveInSquare() {
	for (int i = 0; i < 4; i++) {
		mecanum.mecRun(3.0, 1.57*i, 0);
		delay(1000);
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

void FollowSide() {
	lineFollowerControl.setSide(LineFollowControl::LEFT);
	lineFollowerControl.followInfinitely();
	mecanum.mecRun(0, 0, 0);
	delay(2000);
}

void ReadSensorData() {
	QTRSensorsRC* sensor = lineFollowerControl.getFrontSensor();

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
