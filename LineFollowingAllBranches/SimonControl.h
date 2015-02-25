

class ArmControl;

class SimonControl
{
	// Wrapper for the Simon functions
private:
	ArmControl* parent;

public:
	SimonControl(ArmControl* parent) : parent(parent) {}
	void Play();
	void Grab();
	void Release();
	void Simon_Play();
	const int MAX_SEQUENCE = 32;
	const int TimeConstant = 1.5;
	int get_color();
	void play_sequence(int curr, int sequence[], unsigned long end_t);
	void press_red();
	void press_blue();
	void press_green();
	void press_yellow();
	void move_down(double x, double y, double z, signed int g, signed int r, signed int a);
};