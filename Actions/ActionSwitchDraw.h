#ifndef ACTION_SWITCH_Draw_H
#define ACTION_SWITCH_Draw_H

#include "Action.h"

class ActionSwitchDraw : public Action
{
public:
	ActionSwitchDraw(ApplicationManager* pApp);
	virtual void Execute();
};
#endif
