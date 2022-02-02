#ifndef ACTION_RESTART_PLAY_H
#define ACTION_RESTART_H

#include "Action.h"

class ActionRestartPlay : public Action
{
public:
	ActionRestartPlay(ApplicationManager* pApp);
	virtual void Execute();
};
#endif
