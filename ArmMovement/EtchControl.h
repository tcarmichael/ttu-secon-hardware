
class ArmControl;

class EtchControl
{
	// Wrapper for the Etch-A-Sketch functions
private:
	ArmControl* parent;

public:
	EtchControl(ArmControl* parent) : parent(parent) {}

	void Etch_Play();
	void makeSpace();
	void letterI();
	void letterE();
	void down();
	void Pull();
	void Grasp();
};