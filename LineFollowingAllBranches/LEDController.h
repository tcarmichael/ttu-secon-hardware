// LEDController.h

#ifndef _LEDCONTROLLER_h
#define _LEDCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


class LEDController
{


public:

	void LED_Setup();
	void Orange_On_For(int timer);
	void Red_On_For(int timer);
	void White_On_For(int timer);
	void Blue_On_For(int timer);
	void Green_On_For(int timer);
	void Orange_On();
	void Red_On();
	void White_On();
	void Blue_On();
	void Green_On();
	void Orange_Off();
	void Red_Off();
	void White_Off();
	void Blue_Off();
	void Green_Off();




};

#endif

