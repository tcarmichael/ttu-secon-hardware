#include <QTRSensors.h>

const int NUM_SENSORS = 8;
const int TIMEOUT = 2500;
const int EMITTER_PIN = 2;

QTRSensorsRC qtrrc( (unsigned char[]) {31, 33, 35, 37, 39, 41, 43, 45}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

void setup() {
  // Calibrate the line-following sensor
  delay(500);
  pinMode(13, OUTPUT); // turn on the built-in LED
  digitalWrite(13, HIGH);
  
  for (int i = 0; i < 400; i++) {
    qtrrc.calibrate();
  }
  digitalWrite(13, LOW); // turn off the built-in LED
  
  // Print the calibration minimum and maximum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print("Min: ");
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(" Max: ");
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.println();
  }
}

void loop() {
  // Read calibrated sensor values
  unsigned int position = qtrrc.readLine(sensorValues);
  
  for (unsigned char i = 0; i < NUM_SENSORS; i++) {
    Serial.print(sensorValues[i]);
    Serial.print(' ');
  }
  
  Serial.print(position);
  
  delay(250);
}
