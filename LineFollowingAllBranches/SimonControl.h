

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
	const int TimeConstant = 0.5;
	int get_color();
	void play_sequence(int curr, int sequence[]);
	void press_red();
	void press_blue();
	void press_green();
	void press_yellow();
};