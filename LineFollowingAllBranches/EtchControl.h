#include "GameControl.h"

class GameControl;

class EtchControl : public GameControl
{
	// Wrapper for the Etch-A-Sketch functions
private:
	const int closeRearGripper = 95;
	const int openRearGripper = 50;
	const int closeFrontGripper = 145;
	const int openFrontGripper = 90;
	const int timing = 180;
	const int Clawtiming = 50;
	int count = 0;

public:
	EtchControl(ArmControl* parent) : GameControl(parent) {}

	void Play();
	void makeSpace();
	int letterAdown();
	int letterAup();
	int letterBdown();
	int letterBup();
	int letterCdown();
	int letterCup();
	int letterDdown();
	int letterDup();
	int letterEup();
	int letterEdown();
	int letterFup();
	int letterFdown();
	int letterGup();
	int letterGdown();
	int letterHdown();
	int letterHup();
	int letterIdown();
	int letterIup();
	int letterJdown();
	int letterJup();
	int letterKdown();
	int letterKup();
	int letterLdown();
	int letterLup();
	int letterMdown();
	int letterMup();
	int letterNdown();
	int letterNup();
	int letterOdown();
	int letterOup();
	int letterPdown();
	int letterPup();
	int letterQdown();
	int letterQup();
	int letterRdown();
	int letterRup();
	int letterSdown();
	int letterSup();
	int letterTdown();
	int letterTup();
	int letterUdown();
	int letterUup();
	int letterVdown();
	int letterVup();
	int letterWdown();
	int letterWup();
	void down();
	void up();
	void Pull();
	void Grasp();
	void Release();
	void ReleaseDemo();
	void draw();
	void draw_savannah();
	void resetFrontLeft();
	void resetFrontRight();
	void resetRearLeft();
	void resetRearRight();
	void diagonalUpLtR();
};
