#include "GameControl.h"

class GameControl;

class CardControl : public GameControl
{
	// Wrapper for the Simon functions

public:
	CardControl(ArmControl* parent) : GameControl(parent) {}
	void Play();
};