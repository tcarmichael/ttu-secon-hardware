#include <QTRSensors.h>
#include "../../LineFollowControl.h"
#include <Mecanum.h>

#define NUM_SENSORS   8     // number of sensors used
unsigned int sensorValues[NUM_SENSORS];

Mecanum mecanum;
LineFollowerControl control(&mecanum);

void setup()
{
	// Stop the robot
	mecanum.begin();

	// Initialize the line following
	control.begin();
}


void loop()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtrrc.read(sensorValues); instead of unsigned int position = qtrrc.readLine(sensorValues);
  unsigned int position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 1);
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  //Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position); // comment this line out if you are using raw values
  
  delay(250);
}
