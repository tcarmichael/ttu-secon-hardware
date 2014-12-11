
class ArmControl;

class EtchControl
{
	// Wrapper for the Etch-A-Sketch functions
private:
	ArmControl* parent;
	const int closeRearGripper = 83;
	const int openRearGripper = 50;
	const int closeFrontGripper = 145;
	const int openFrontGripper  = 90;
	const int timing = 250;
	int count = 0;

public:
	EtchControl(ArmControl* parent) : parent(parent) {}

	void Etch_Play();
	void makeSpace();
	void letterI();
	void letterE();
	void down();
	void Pull();
	void Grasp();
	void Release();
	void draw();
};