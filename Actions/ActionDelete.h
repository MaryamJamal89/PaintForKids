#ifndef ACTION_DELETE_H
#define ACTION_DELETE_H

#include "Action.h"

class ActionDelete : public Action
{
public:
	ActionDelete(ApplicationManager* pApp);

	virtual void Execute();
};

#endif