#ifndef ACTION_ADD_ELLIPSE_H
#define ACTION_ADD_ELLIPSE_H

#include "Action.h"
#include "../GUI/GUI.h"
#include "../Figures/CEllipse.h"
#include "../ApplicationManager.h"

//Add Ellipse Action class
class ActionAddEllipse : public Action
{
public:
	ActionAddEllipse(ApplicationManager* pApp);

	//Add Ellipse to the ApplicationManager
	virtual void Execute();
	void CheckPoint(GUI* pGUI, Point& point, string mssg);
};

#endif