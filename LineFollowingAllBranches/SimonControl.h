#include "GameControl.h"

class GameControl;

class SimonControl : public GameControl
{
	// Wrapper for the Simon functions
public:
	SimonControl(ArmControl* parent) : GameControl(parent) {}
	void Play();
	void Grab();
	void Release();
	void Simon_Play();
	const int MAX_SEQUENCE = 32;
	const int TimeConstant = 1.5;
	int get_color();
	void play_sequence(int curr, int sequence[], unsigned long end_t);
	void press_red(unsigned long end_t);
	void press_blue(unsigned long end_t);
	void press_green(unsigned long end_t);
	void press_yellow(unsigned long end_t);
	void move_down(double x, double y, double z, signed int g, signed int r, signed int a, unsigned long end_t);
};