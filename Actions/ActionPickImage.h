#ifndef ACTION_PICK_IMAGE_H
#define ACTION_PICK_IMAGE_H

#include "Action.h"

class ActionPickImage : public Action
{
private:
	int *playType;
public:
	ActionPickImage(ApplicationManager* pApp,int & _playType);
	virtual void Execute();
};

#endif