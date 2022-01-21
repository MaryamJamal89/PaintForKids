#ifndef ACTION_ADD_ELLIPSE_H
#define ACTION_ADD_ELLIPSE_H

#include "Action.h"

//Add Square Action class
class ActionAddEllipse : public Action
{
public:
	ActionAddEllipse(ApplicationManager* pApp);

	//Add Ellipse to the ApplicationManager
	virtual void Execute();
};

#endif