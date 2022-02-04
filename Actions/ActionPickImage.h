#ifndef ACTION_PICK_IMAGE_H
#define ACTION_PICK_IMAGE_H

#include "Action.h"
#include "ActionPickImage_Color.h"

class ActionPickImage : public ActionPickImage_Color
{
private:
public:
	ActionPickImage(ApplicationManager* pApp);
	virtual bool figureMatches(CFigure* figure, CFigure* selectedFigure);
	void UpdateStatusBar(CFigure* fig);
};

#endif