#include "GameControl.h"

class RubiksControl : public GameControl
{
	// Wrapper for the Rubik's cube functions

public:
	RubiksControl(ArmControl* parent) : GameControl(parent) {}
	void Grab();
	void Rotate();
	void Release();
	void Play();
};