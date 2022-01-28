#ifndef ACTION_LOAD_H
#define ACTION_LOAD_H

#include "Action.h"

class ActionLoad : public Action
{
public:
	ActionLoad(ApplicationManager* pApp);

	virtual void Execute();
};

#endif