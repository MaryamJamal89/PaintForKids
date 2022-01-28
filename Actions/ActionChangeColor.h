#include "Action.h"

//Add Square Action class
class ActionChangeColor : public Action
{
private:
	color colour;
	int DrawOrFill;
public:
	ActionChangeColor(ApplicationManager* pApp, color c, int DrawOrFill);

	//Add Square to the ApplicationManager
	virtual void Execute();

};