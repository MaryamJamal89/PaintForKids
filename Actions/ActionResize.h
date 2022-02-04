#pragma once
#ifndef ACTION_RESIZE_H
#define ACTION_RESIZE_H

#include "Action.h"


class ActionResize :public Action
{
	Point P;
	ActionType SCALE;
	double Scale;
	bool anySelected;
public:
	ActionResize(ApplicationManager* pApp);


	virtual bool ReadActionParameters();

	bool GetScale(ActionType S);

	virtual void Execute();

};
#endif
