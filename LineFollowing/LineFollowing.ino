#include <Mecanum.h>

#include <Wire.h>

#include <QTRSensors.h>
#include <Adafruit_MotorShield.h>

const int FOLLOWER_OFFSET = 3500;

// PID constants
const double Kp = 1.0f / FOLLOWER_OFFSET; // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
const double Kd = 0.0005f; // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd)

// Line follower connections
const int NUM_SENSORS = 8;     // number of sensors used
const int EMITTER_PIN = 40;     // Line-following sensor emitter
unsigned char SENSOR_PINS[] = {22, 24, 26, 28, 30, 32, 34, 36};
const unsigned int TIMEOUT = 2000;

QTRSensorsRC qtrrc(SENSOR_PINS, NUM_SENSORS, TIMEOUT);

// Interacts with the mecanum wheels and the motor shield
Mecanum mecanum;

void setup() {
	Serial.begin(9600);
	Serial.println("Starting calibration");

	// Calibrate the line-following sensor
	delay(500);

	for (int i = 0; i < 400; i++) {
		qtrrc.calibrate();
	}

	// Print the calibration minimum and maximum values measured when emitters were on
	for (int i = 0; i < NUM_SENSORS; i++) {
		Serial.print("Min: ");
		Serial.print(qtrrc.calibratedMinimumOn[i]);
		Serial.print(" Max: ");
		Serial.print(qtrrc.calibratedMaximumOn[i]);
		Serial.println();
	}
} 

int lastError = 0;

void loop() {
	// Get line follower readings
	unsigned int sensors[NUM_SENSORS];
	int position = qtrrc.readLine(sensors, QTR_EMITTERS_ON, 1);

	// Calculate the error
	// Positive error is to the left; negative error is to the right
	int error = position - FOLLOWER_OFFSET;

	// Convert the error into a motor speed
	double rotation = Kp * error + Kd * (error - lastError);

	lastError = error;

	// Bounds-checking
	rotation = (rotation > 1) ? 1 : rotation;
	rotation = (rotation < -1) ? -1 : rotation;
	
	// Send the speed
	if (error == -FOLLOWER_OFFSET || error == FOLLOWER_OFFSET) {
		mecanum.mecRun(0, 0, rotation);
	} else {
		mecanum.mecRun(0.75, 0, rotation);
	}
	
	// Display the results
	Serial.print(position);
	Serial.print(' ');
	Serial.print(error);
	Serial.print(' ');
	Serial.print(rotation);
	Serial.println();
}
