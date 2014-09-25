// demo of rfbee send and recv
#include <Arduino.h>
#include <Wire.h>

const int ADDRESS = 4;

unsigned char rxData1[200];               // data len
unsigned char len1;                       // len
unsigned char srcAddress1;
unsigned char destAddress1;
char rssi1;
unsigned char lqi1;
int result1;

unsigned char cntGetDta = 5;

void setup() {
    pinMode(10, OUTPUT);
    
    Wire.begin();
    
    Serial.begin(9600);
}

void loop() {
    if(RFBEE.isDta()) {
        result1 = receiveData(rxData1, &len1, &srcAddress1, &destAddress1, (unsigned char *)&rssi1 , &lqi1);
        Serial.println(len1);
        for(int i = 0; i< len1; i++) {
            Serial.print(rxData1[i]);Serial.print("\t");
        }
        
        Serial.println();
        
        sendToI2C(6, rxData1);
    }
}

void sendToI2C(unsigned char ilen, unsigned char *idata) {
    Wire.beginTransmission(ADDRESS);
    
    // Send one byte
    for(int i = 0; i<ilen; i++) {
      Wire.write(idata[i]);
    }
    
    Wire.endTransmission();                              // stop transmitting
}
