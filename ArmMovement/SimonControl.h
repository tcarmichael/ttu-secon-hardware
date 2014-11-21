
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
};