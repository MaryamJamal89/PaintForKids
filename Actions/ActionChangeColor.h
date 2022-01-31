#include "Action.h"
#include"../Figures/CFigure.h"


//Add Square Action class
class ActionChangeColor : public Action
{
private:
	color colour;
	int DrawOrFill;
	CFigure* Figure;
public:
	ActionChangeColor(ApplicationManager* pApp, color c, int DrawOrFill, CFigure* );

	//Add Square to the ApplicationManager
	virtual void Execute();

};