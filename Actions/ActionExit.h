#ifndef ACTION_EXIT_H
#define ACTION_EXIT_H
#include "Action.h"

class ActionExit : public Action
{
public:
	ActionExit(ApplicationManager* pApp);

	virtual void Execute();

};

#endif