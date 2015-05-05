#include "GameControl.h"

class GameControl;

class EtchControl : public GameControl
{
	// Wrapper for the Etch-A-Sketch functions
private:
	const int closeRearGripper = 95;
	const int openRearGripper = 50;
	const int closeFrontGripper = 145;
	const int openFrontGripper  = 90;
	const int timing = 180;
	const int Clawtiming = 50;
	int count = 0;

public:
	EtchControl(ArmControl* parent) : GameControl(parent) {}

	void Play();
	void makeSpace();
	void letterI();
	void letterEup();
	void letterEdown();
	void letterSdown();
	void letterAdown();
	void letterAup();
	void letterBdown();
	void letterBup();
	void letterCdown();
	void letterCup();
	void letterDdown();
	void letterDup();
	void letterVdown();
	void letterNdown();
	void letterNup();
	void letterHdown();
	void down();
	void up();
	void Pull();
	void Grasp();
	void Release();
	void draw();
	void draw_savannah();
	void resetFrontLeft();
	void resetFrontRight();
	void resetRearLeft();
	void resetRearRight();
	void diagonalUpLtR();
};