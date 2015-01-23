
class ArmControl;

class EtchControl
{
	// Wrapper for the Etch-A-Sketch functions
private:
	ArmControl* parent;
	const int closeRearGripper = 90;
	const int openRearGripper = 60;
	const int closeFrontGripper = 130;
	const int openFrontGripper  = 60;

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