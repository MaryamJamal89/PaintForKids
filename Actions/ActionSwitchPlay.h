#ifndef ACTION_SWITCH_PLAY_H
#define ACTION_SWITCH_PLAY_H

#include "Action.h"

class ActionSwitchPlay : public Action
{
public:
	ActionSwitchPlay(ApplicationManager* pApp);

	//Add toolbar to the ApplicationManager
	virtual void Execute();
};
#endif