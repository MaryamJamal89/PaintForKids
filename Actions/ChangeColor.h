#include "Action.h"

//Add Square Action class
class ChangeColor : public Action
{
private:
	color colour;
	int DrawOrFill;
public:
	ChangeColor(ApplicationManager* pApp, color c, int DrawOrFill);

	//Add Square to the ApplicationManager
	virtual void Execute();

};