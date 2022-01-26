#ifndef ACTION_CHANGE_LOCATION_H
#define ACTION_CHANGE_LOCATION_H

#include "Action.h"

class ActionChangeLocation : public Action
{
	bool isFront;
public:
	ActionChangeLocation(ApplicationManager* pApp, bool isFront);

	virtual void Execute();

};

#endif