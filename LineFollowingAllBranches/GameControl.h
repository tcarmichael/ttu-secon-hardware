// GameControl.h

#ifndef _GAMECONTROL_h
#define _GAMECONTROL_h

class ArmControl;

class GameControl
{
 protected:
	ArmControl* parent;

 public:
	GameControl(ArmControl* parent) : parent(parent) {}
	virtual void Play(void) = 0;
};

#endif

