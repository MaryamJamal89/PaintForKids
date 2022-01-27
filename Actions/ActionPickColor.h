#ifndef ACTION_PICK_COLOR_H
#define ACTION_PICK_COLOR_H

#include "Action.h"


class ActionPickColor :public Action
{
public:
	ActionPickColor(ApplicationManager* pApp);
	virtual void Execute();
};
#endif
