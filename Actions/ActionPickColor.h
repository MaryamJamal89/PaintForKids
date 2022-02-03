#ifndef ACTION_PICK_COLOR_H
#define ACTION_PICK_COLOR_H

#include "Action.h"
#include "ActionPickImage_Color.h"


class ActionPickColor :public ActionPickImage_Color
{
public:
	ActionPickColor(ApplicationManager* pApp);
	virtual bool figureMatches(CFigure* figure, CFigure* selectedFigure);
	void UpdateStatusBar(CFigure* fig);
};
#endif


