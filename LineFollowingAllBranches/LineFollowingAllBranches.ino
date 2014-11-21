#include "LineFollowControl.h"
#include "Mecanum.h"
#include "Wire.h"
#include "QTRSensors.h"
#include "Adafruit_MotorShield.h"

// Interacts with the mecanum wheels and the motor shield
Mecanum mecanum;

LineFollowControl lineFollowerControl(&mecanum);
Adafruit_PWMServoDriver pwm;

void setup() {
	Serial.begin(9600);

	// Initialize the mecanum wheels
	Serial.println("Initializing the mecanum wheels");
	mecanum.begin();
	
	// Calibrate the line followers
	Serial.println("Calibrating");
	delay(500);
	lineFollowerControl.defaultCalibration();

	// Remove this
	pwm.begin();
	pwm.setPWMFreq(60);
	Arm_Front_Home_Right();
	Arm_Rear_Home_Right();
	
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

void followLine() {
	// Follow the front line sensor until the left line sensor finds a line
	Serial.println("Following the front line sensor");
	delay(1000);
	lineFollowerControl.setSide(LineFollowControl::FRONT);
	/*lineFollowerControl.followUntilLine(LineFollowControl::LEFT);
	delay(100);

	Serial.println("Turn left 90");
	lineFollowerControl.RotateUntilLine(-1.0);
	delay(100);*/

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
	delay(2000);

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
	delay(2000);

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
void Arm_Front_Home_Right()
{
	Front_Arm_IK(1, 0, 2, 90, 90, -30);
	delay(1500);
}
void Arm_Rear_Home_Right()
{
	Rear_Arm_IK(-1, 0, 2, 90, 90, -30);
	delay(1500);
}


const double A = 4.75;
const double B = 5.00;

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  650 // this is the 'maximum' pulse length count (out of 4096)

const int NUM_SERVOS = 6;
const int Front_Arm[NUM_SERVOS] = { 8, 9, 11, 12, 13, 14 };// skips 12 intentionally
const int Rear_Arm[NUM_SERVOS] = { 0, 1, 2, 3, 4, 5 };

int Rear_Arm_IK(double x, double y, double z, int g, double wr, int wa) // Note xy are coordinates in the ground plane and z is the vertical plane
{

	double r = sqrt(x*x + y*y);
	z = z + r*(.5);
	wa = wa + 3 * r;
	double Base_Rotation = degrees(atan2(y, x));
	double M = sqrt((z*z) + (r*r));

	if (M <= 0)
	{
		Serial.print("M");
		return 1;

	}
	double A1 = atan(z / r);
	if (r <= 0)
	{
		Serial.print("r");
		return 1;

	}
	double A2 = acos((A*A - B*B + M*M) / ((A * 2)*M));
	double Elbow = acos((A*A + B*B - M*M) / ((A * 2)*B));
	double Shoulder = A1 + A2;
	Elbow = degrees(Elbow);
	Shoulder = degrees(Shoulder);
	if ((int)Elbow <= 0 || (int)Shoulder <= 0)
	{
		Serial.print("S");
		return 1;

	}
	double Wris = abs(wa - Elbow - Shoulder) - 90;

	double pulselen;

	pulselen = map(Shoulder, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Rear_Arm[1], 0, pulselen);


	pulselen = map(180 - Elbow, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Rear_Arm[2], 0, pulselen);



	pulselen = map(180 - Wris, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Rear_Arm[3], 0, pulselen);


	pulselen = map(Base_Rotation, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Rear_Arm[0], 0, pulselen);


	pulselen = map(wr, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Rear_Arm[4], 0, pulselen);

	pulselen = map(g, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Rear_Arm[5], 0, pulselen);


	return 0;
}



int Front_Arm_IK(double x, double y, double z, int g, double wr, int wa)
{
	double r = sqrt(x*x + y*y);
	z = z + r*(.5);
	wa = wa + 1.5*r;
	double Base_Rotation = degrees(atan2(y, x));
	double M = sqrt((z*z) + (r*r));
	if (M <= 0)
		return 1;
	double A1 = atan(z / r);
	if (r <= 0)
		return 1;
	double A2 = acos((A*A - B*B + M*M) / ((A * 2)*M));
	double Elbow = acos((A*A + B*B - M*M) / ((A * 2)*B));
	double Shoulder = A1 + A2;
	Elbow = degrees(Elbow);
	Shoulder = degrees(Shoulder);
	if ((int)Elbow <= 0 || (int)Shoulder <= 0)
		return 1;
	double Wris = abs(wa - Elbow - Shoulder) - 90;


	double pulselen;

	pulselen = map(Shoulder, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Front_Arm[1], 0, pulselen);


	pulselen = map(180 - Elbow, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Front_Arm[2], 0, pulselen);



	pulselen = map(180 - Wris, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Front_Arm[3], 0, pulselen);


	pulselen = map(Base_Rotation, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Front_Arm[0], 0, pulselen);


	pulselen = map(wr, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Front_Arm[4], 0, pulselen);

	pulselen = map(g, 0, 180, SERVOMIN, SERVOMAX);
	pwm.setPWM(Front_Arm[5], 0, pulselen);


	return 0;

}

