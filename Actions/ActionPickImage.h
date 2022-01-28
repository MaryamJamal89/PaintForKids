#ifndef ACTION_PICK_IMAGE_H
#define ACTION_PICK_IMAGE_H

#include "Action.h"

class ActionPickImage : public Action
{
public:
	ActionPickImage(ApplicationManager* pApp);
	virtual void Execute();
};

#endif