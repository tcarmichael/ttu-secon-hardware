#include <seeed_pwm.h>

#include <motordriver_4wd.h>
#include <motordriver_4wd_dfs.h>

#include <QTRSensors.h>

#define Kp 0.01   // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 0.1 // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
#define rightMaxSpeed 45 // max speed of the robot
#define leftMaxSpeed 45 // max speed of the robot
#define rightBaseSpeed 20 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 20  // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORS  5     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor outputs to go low

QTRSensorsRC qtrrc((unsigned char[]) {
  12, 11, 13, 3, 2
} , NUM_SENSORS, TIMEOUT); // sensor connected through analog pins A0 - A5 i.e. digital pins 14-19

unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  Serial.begin(9600);
  Serial.println("Basic Line Following");
  
  delay(500);
  Serial.println("Begin Calibration");
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }

  // print the calibration minimum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
  
  MOTOR.init();

  /* comment out for serial printing

  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  */
}

int lastError = 0;

void loop()
{
  unsigned int sensors[NUM_SENSORS];
  int position = qtrrc.readLine(sensors, QTR_EMITTERS_ON, true); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
  int error = position - 2000;
  
  Serial.print(error);
  Serial.print('\t');
  Serial.println(position);

  int motorSpeed = Kp * error + Kd * (error - lastError);
  lastError = error;

  int rightMotorSpeed = rightBaseSpeed + motorSpeed;
  int leftMotorSpeed = leftBaseSpeed - motorSpeed;

  // Switch the motor direction for negatives
  unsigned char rightDirection = DIRF;
  unsigned char leftDirection = DIRR;
  if (rightMotorSpeed < 0) {
   rightMotorSpeed = -rightMotorSpeed;
   rightDirection = DIRR;
  }
  if (leftMotorSpeed < 0) {
    leftMotorSpeed = -leftMotorSpeed;
    leftDirection = DIRF;
  }

  if (rightMotorSpeed > rightMaxSpeed) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed

  {
    MOTOR.setSpeedDir1(leftMotorSpeed, leftDirection);
    MOTOR.setSpeedDir2(rightMotorSpeed, rightDirection);
  }
}
