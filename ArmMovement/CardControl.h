
class ArmControl;

class CardControl
{
	// Wrapper for the Simon functions
private:
	ArmControl* parent;

public:
	CardControl(ArmControl* parent) : parent(parent) {}
	void Card_Play();
};