#ifndef ACTION_PICK_IMAGE_COLOR_H
#define ACTION_PICK_IMAGE_COLOR_H

#include "Action.h"

class ActionPickImage_Color : public Action
{
public:
	ActionPickImage_Color(ApplicationManager* pApp);
	virtual void Execute();
};

#endif
