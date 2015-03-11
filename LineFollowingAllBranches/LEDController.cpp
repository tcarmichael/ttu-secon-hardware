// 
// 
// 

#include "LEDController.h"




void LEDController::LED_Setup(){
	pinMode(30, OUTPUT);
	pinMode(31, OUTPUT);
	pinMode(32, OUTPUT);
	pinMode(33, OUTPUT);
	pinMode(34, OUTPUT);
	digitalWrite(34, LOW);
	digitalWrite(33, LOW);
	digitalWrite(32, LOW);
	digitalWrite(31, LOW);
	digitalWrite(30, LOW);
	

}




void LEDController::Orange_On_For(int timer){
	digitalWrite(30, HIGH);
	delay(timer);
	digitalWrite(30, LOW);

}

void LEDController::Red_On_For(int timer){
	digitalWrite(31, HIGH);
	delay(timer);
	digitalWrite(31, LOW);

}

void LEDController::White_On_For(int timer){
	digitalWrite(32, HIGH);
	delay(timer);
	digitalWrite(32, LOW);

}

void LEDController::Blue_On_For(int timer){
	digitalWrite(33, HIGH);
	delay(timer);
	digitalWrite(33, LOW);

}

void LEDController::Green_On_For(int timer){
	digitalWrite(34, HIGH);
	delay(timer);
	digitalWrite(34, LOW);

}






void LEDController::Orange_On(){
	digitalWrite(30, HIGH);

}

void LEDController::Red_On(){
	digitalWrite(31, HIGH);

}

void LEDController::White_On(){
	digitalWrite(32, HIGH);

}

void LEDController::Blue_On(){
	digitalWrite(33, HIGH);

}

void LEDController::Green_On(){
	digitalWrite(34, HIGH);

}







void LEDController::Orange_Off(){

	digitalWrite(30, LOW);

}

void LEDController::Red_Off(){

	digitalWrite(31, LOW);

}

void LEDController::White_Off(){

	digitalWrite(32, LOW);

}

void LEDController::Blue_Off(){

	digitalWrite(33, LOW);

}

void LEDController::Green_Off(){

	digitalWrite(34, LOW);

}
