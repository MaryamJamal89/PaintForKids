#pragma once
#ifndef ACTION_RESIZE_H
#define ACTION_RESIZE_H

#include "Action.h"


class ActionResize :public Action
{
	double Scale;
	bool anySelected;

public:
	ActionResize(ApplicationManager* pApp,double _Scale);
	virtual void Execute();

};
#endif
