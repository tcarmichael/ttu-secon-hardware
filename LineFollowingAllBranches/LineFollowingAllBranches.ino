#include "LineFollowControl.h"
#include "Mecanum.h"
#include "Wire.h"
#include "QTRSensors.h"
#include "Adafruit_MotorShield.h"

// Interacts with the mecanum wheels and the motor shield
Mecanum mecanum;

LineFollowControl lineFollowerControl(&mecanum);

void setup() {
	Serial.begin(9600);

	// Initialize the mecanum wheels
	Serial.println("Initializing the mecanum wheels");
	mecanum.begin();
	
	// Calibrate the line followers
	Serial.println("Calibrating");
	delay(500);
	lineFollowerControl.defaultCalibration();
	
	// Begin line following
	Serial.println("Starting line following");
	followLine();
}

void followLine() {
	// Follow the front line sensor until the left line sensor finds a line
	Serial.println("Following the front line sensor");
	delay(1000);
	lineFollowerControl.setSide(LineFollowControl::RIGHT);
	lineFollowerControl.followInfinitely();
	lineFollowerControl.followUntilLine(LineFollowControl::LEFT);
	delay(1000);

	Serial.println("Following the left line sensor");
	lineFollowerControl.setSide(LineFollowControl::LEFT);
	lineFollowerControl.followUntilWhite();
	delay(1000);

	Serial.println("Following the right line sensor");
	lineFollowerControl.setSide(LineFollowControl::RIGHT);
	lineFollowerControl.followUntilLine(LineFollowControl::FRONT);
	delay(1000);

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

	Serial.println("Done");
}

void loop() {
	/*for (int i = 0; i < 4; i++) {
		mecanum.mecRun(3.0, 1.57*i, 0);
		delay(1000);
	}*/
	/*QTRSensorsRC* sensor = lineFollowerControl.getLeftSensor();

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

	delay(1000);*/
}
