#include "LineFollowControl.h"
#include <Mecanum.h>

#include <Wire.h>

#include <QTRSensors.h>
#include <Adafruit_MotorShield.h>

LineFollowControl lineFollowerControl;

// Interacts with the mecanum wheels and the motor shield
Mecanum mecanum;

void setup() {
	Serial.begin(9600);
	
	// Calibrate the line followers
	Serial.println("Calibrating");
	delay(500);
	lineFollowerControl.calibrate();
	
	// Initialize the mecanum wheels
	Serial.println("Initializing the mecanum wheels");
	mecanum.begin();
	
	// Begin line following
	Serial.println("Starting line following");
	followLine();
}

void followLine() {
	// Follow the front line sensor until it detects all white
	Serial.println("Following the front line sensor");
	delay(1000);
	lineFollowerControl.followUntilWhite(lineFollowerControl.getFrontSensor(), mecanum);
}

void loop() {
	// Empty
}
