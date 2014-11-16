
class ArmControl;

class RubiksControl
{
	// Wrapper for the Rubik's cube functions
private:
	ArmControl* parent;

public:
	RubiksControl(ArmControl* parent) : parent(parent) {}
	void Grab();
	void Rotate();
};