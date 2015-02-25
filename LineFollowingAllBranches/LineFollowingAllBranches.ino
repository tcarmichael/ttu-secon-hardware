#include "LineFollowControl.h"
#include "Mecanum.h"
#include "Wire.h"
#include "QTRSensors.h"
#include "Adafruit_MotorShield.h"
#include "ArmControl.h"
#include "Adafruit_Light_Sensor\Adafruit_TSL2561_U.h"
#include "Adafruit_Sensor\Adafruit_Sensor.h"
#include "LEDControl.h"


// Interacts with the mecanum wheels and the motor shield
Mecanum mecanum;
LineFollowControl lineFollowerControl(&mecanum);

// Controls the arm movements
ArmControl arm;


void setup() {
	Serial.begin(9600);
	// Used to initialize the LEDs :)
	LED_Setup();

	//Example code Line for LEDs, just change the color word

	Orange_On();
	Green_On_For(2000);
	Orange_Off();
	
	// uncomment for David's code testing
	arm.begin();
	arm.Simon.Simon_Play();
	delay(15000);
	
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


	//arm.Etch.Etch_Play();

	// Wait for start signal
	Serial.println("Waiting for LED");
	WaitForLed();

	// Get out of the box
	mecanum.mecRun(0.9, 0, 0);
	delay(1000);
	mecanum.mecRun(0, 0, 0);

	// Begin line following
	Serial.println("Starting line following");
	
	FollowLineMecanum(); 
	//followLine();
}

void loop() {
	/*lineFollowerControl.setSide(LineFollowControl::RIGHT);
	ReadSensorData();*/
	//FollowSide(LineFollowControl::FRONT);
	//SpeedRamping();
	//MoveInSquare(true);
	//Strafe();
	

}
void LED_Setup(){
	pinMode(14, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(16, OUTPUT);
	pinMode(17, OUTPUT);
	pinMode(18, OUTPUT);
	digitalWrite(18, LOW);
	digitalWrite(17, LOW);
	digitalWrite(16, LOW);
	digitalWrite(15, LOW);
	digitalWrite(14, LOW);


}
void Orange_On_For(int timer){
	digitalWrite(14, HIGH);
	delay(timer);
	digitalWrite(14, LOW);

}

void Red_On_For(int timer){
	digitalWrite(15, HIGH);
	delay(timer);
	digitalWrite(15, LOW);

}

void White_On_For(int timer){
	digitalWrite(16, HIGH);
	delay(timer);
	digitalWrite(16, LOW);

}

void Blue_On_For(int timer){
	digitalWrite(17, HIGH);
	delay(timer);
	digitalWrite(17, LOW);

}

void Green_On_For(int timer){
	digitalWrite(18, HIGH);
	delay(timer);
	digitalWrite(18, LOW);

}






void Orange_On(){
	digitalWrite(14, HIGH);
	
}

void Red_On(){
	digitalWrite(15, HIGH);
	
}

void White_On(){
	digitalWrite(16, HIGH);

}

void Blue_On(){
	digitalWrite(17, HIGH);

}

void Green_On(){
	digitalWrite(18, HIGH);

}







void Orange_Off(){
	
	digitalWrite(14, LOW);
	
}

void Red_Off(){

	digitalWrite(15, LOW);

}

void White_Off(){

	digitalWrite(16, LOW);

}

void Blue_Off(){

	digitalWrite(17, LOW);

}

void Green_Off(){

	digitalWrite(18, LOW);

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

	do {
		tsl.getEvent(&event);
	} while (event.light);
}

void followLine()
{
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

	mecanum.mecRun(-1.0, 0, 0);
	delay(200);
	mecanum.mecRun(0, 0, 0);
	delay(100);
	
	lineFollowerControl.RotateUntilLine(1.0, LineFollowControl::RIGHT);
	delay(100);

	// And boom goes the dynamite
	lineFollowerControl.CenterOnLine(LineFollowControl::LEFT, LineFollowControl::RIGHT);
	delay(100);

	// Play Simon here
	Serial.println("Play Simon");
	arm.Simon.Simon_Play();

	Serial.println("Turn right 180");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();

	delay(100);

	Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(200);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	Serial.println("Turn left 90");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);

	mecanum.mecRun(-1.0, 0, 0);
	delay(50);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	Serial.println("Wait on right line sensor");
	lineFollowerControl.followUntilLine(LineFollowControl::RIGHT);
	delay(100);

	Serial.println("Turn right 90");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();
	delay(100);

	mecanum.mecRun(-1.0, 0, 0);
	delay(200);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	lineFollowerControl.RotateUntilLine(-1.0, LineFollowControl::LEFT);
	delay(100);

	// And boom goes the dynamite
	lineFollowerControl.CenterOnLine(LineFollowControl::LEFT, LineFollowControl::RIGHT);
	delay(100);

	// Play game here
	Serial.println("Play Etch-A-Sketch");
	arm.Etch.Etch_Play();

	Serial.println("Turn left 180");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();
	delay(100);

	Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(200);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	Serial.println("Turn right 90");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(100);

	mecanum.mecRun(-1.0, 0, 0);
	delay(50);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	lineFollowerControl.followUntilLine(LineFollowControl::LEFT);
	delay(100);

	Serial.println("Turn left 90");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);

	Serial.println("Following the left line sensor");
	lineFollowerControl.followUntilWhite();
	delay(100);

	mecanum.mecRun(-1.0, 0, 0);
	delay(200);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	lineFollowerControl.RotateUntilLine(1.0, LineFollowControl::RIGHT);
	delay(100);

	// And boom goes the dynamite
	lineFollowerControl.CenterOnLine(LineFollowControl::LEFT, LineFollowControl::RIGHT);

	// Play Rubiks here
	Serial.println("Play Rubik's Cube");
	arm.Rubiks.Rubiks_Play();

	Serial.println("Turn right 180");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();
	delay(100);

	Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(150);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	Serial.println("Turn left 90");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);

	mecanum.mecRun(-1.0, 0, 0);
	delay(50);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	Serial.println("Wait on right line sensor");
	lineFollowerControl.followUntilLine(LineFollowControl::RIGHT);
	delay(100);

	Serial.println("Turn right 90");
	lineFollowerControl.RotateUntilLine(1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();
	delay(100);

	bool oldBoard = false;
	if (oldBoard)
	{
		Serial.println("Go straight");
		mecanum.mecRun(1.0, 0, 0);
		delay(150);
		mecanum.mecRun(0, 0, 0);
		delay(100);

		lineFollowerControl.RotateUntilLine(-1.0, LineFollowControl::LEFT);
		delay(100);
	}
	else
	{
		mecanum.mecRun(-1.0, 0, 0);
		delay(200);
		mecanum.mecRun(0, 0, 0);
		delay(100);

		lineFollowerControl.RotateUntilLine(-1.0, LineFollowControl::LEFT);
		delay(100);

		// And boom goes the dynamite
		lineFollowerControl.CenterOnLine(LineFollowControl::LEFT, LineFollowControl::RIGHT);
		delay(100);
	}

	// Play game here
	arm.Card.Card_Play();
	
	Serial.println("Turn left almost 180");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);

	lineFollowerControl.followUntilWhite();
	delay(100);

	Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(200);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	Serial.println("Turn right 90");
	lineFollowerControl.RotateUntilLine(0.8);
	delay(100);

	Serial.println("Go straight");
	mecanum.mecRun(1.0, 0, 0);
	delay(150);
	mecanum.mecRun(0, 0, 0);
	delay(100);

	lineFollowerControl.followUntilWhite();
	
}

void FollowLineMecanum() {
	Serial.println("Following the front line sensor");
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	lineFollowerControl.followUntilLine(LineFollowControl::LEFT);
	
	Serial.println("Following the left line sensor");
	lineFollowerControl.setSide(LineFollowControl::LEFT);
	lineFollowerControl.followUntilWhite();

	mecanum.mecRun(0.6, PI / 2, 0);
	delay(200);
	lineFollowerControl.CenterOnLine(LineFollowControl::LEFT, LineFollowControl::RIGHT);
	// Play Simon
	//delay(5000);
	arm.Simon.Simon_Play();

	Serial.println("Following the right line sensor");
	lineFollowerControl.setSide(LineFollowControl::RIGHT);
	lineFollowerControl.followUntilLine(LineFollowControl::FRONT);

	Serial.println("Following the front line sensor");
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	lineFollowerControl.followUntilLine(LineFollowControl::RIGHT);

	Serial.println("Following the right line sensor");
	lineFollowerControl.setSide(LineFollowControl::RIGHT);
	lineFollowerControl.followUntilWhite();

	mecanum.mecRun(0.6, 3 * PI / 2, 0);
	delay(200);
	lineFollowerControl.CenterOnLine(LineFollowControl::LEFT, LineFollowControl::RIGHT);
	// Play Etch-A-Sketch
	//delay(5000);
	arm.Etch.Etch_Play();

	Serial.println("Following the left line sensor");
	lineFollowerControl.setSide(LineFollowControl::LEFT);
	lineFollowerControl.followUntilLine(LineFollowControl::FRONT);

	Serial.println("Following the front line sensor");
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	lineFollowerControl.followUntilLine(LineFollowControl::LEFT);

	Serial.println("Following the left line sensor");
	lineFollowerControl.setSide(LineFollowControl::LEFT);
	lineFollowerControl.followUntilWhite();

	mecanum.mecRun(0.6, PI / 2, 0);
	delay(200);
	lineFollowerControl.CenterOnLine(LineFollowControl::LEFT, LineFollowControl::RIGHT);
	// Play the Rubik's cube
	//delay(5000);
	arm.Rubiks.Rubiks_Play();

	Serial.println("Following the right line sensor");
	lineFollowerControl.setSide(LineFollowControl::RIGHT);
	lineFollowerControl.followUntilLine(LineFollowControl::FRONT);

	Serial.println("Following the front line sensor");
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	lineFollowerControl.followUntilLine(LineFollowControl::RIGHT);

	Serial.println("Following the right line sensor");
	lineFollowerControl.setSide(LineFollowControl::RIGHT);
	lineFollowerControl.followUntilWhite();


	mecanum.mecRun(0.6, 3 * PI / 2, 0);
	delay(200);
	lineFollowerControl.CenterOnLine(LineFollowControl::LEFT, LineFollowControl::RIGHT);
	// Pick up the card
	//delay(5000);
	arm.Card.Card_Play();

	Serial.println("Following the left line sensor");
	lineFollowerControl.setSide(LineFollowControl::LEFT);
	lineFollowerControl.followUntilLine(LineFollowControl::FRONT);

	Serial.println("Following the front line sensor");
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	lineFollowerControl.followUntilWhite();

	Serial.println("Done");
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
	double max_speed = 1.5;

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
