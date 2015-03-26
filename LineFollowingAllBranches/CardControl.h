#include "GameControl.h"

class GameControl;

class CardControl : GameControl
{
	// Wrapper for the Simon functions

public:
	CardControl(ArmControl* parent) : GameControl(parent) {}
	void Play();
};