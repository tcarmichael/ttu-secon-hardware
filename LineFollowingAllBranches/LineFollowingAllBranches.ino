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
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	lineFollowerControl.followUntilLine(LineFollowControl::LEFT);
	Serial.println("Finished line following");

	lineFollowerControl.setSide(LineFollowControl::LEFT);
	lineFollowerControl.followUntilWhite();
	Serial.println("Done");
}

void loop() {
	/*QTRSensorsRC* sensor = lineFollowerControl.getLeftSensor();

	unsigned int sensorValues[8];
	sensor->read(sensorValues);
	for (int i = 0; i < 8; i++) {
		Serial.print(sensorValues[i]);
		Serial.print(' ');
	}
	Serial.println();*/
}
