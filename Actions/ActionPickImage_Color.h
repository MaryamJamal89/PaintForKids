#ifndef ACTION_PICK_IMAGE_COLOR_H
#define ACTION_PICK_IMAGE_COLOR_H
#include "..\Figures\CFigure.h"
#include "Action.h"
#define size 200

class ActionPickImage_Color : public Action
{
	
private:
	//void picFiguresStatus();
	CFigure* fig;
	Point point;


	/*playType = 0;*/
	int validCounter;
	int invalidCounter;
	int figCount ;
	//startPlay = 0;

public:
	ActionPickImage_Color(ApplicationManager* pApp);
	virtual CFigure* ReadesFigures();
	virtual void Execute();
	virtual bool figureMatches(CFigure * figure , CFigure * selectedFigure);
	virtual void UpdateStatusBar(CFigure* fig);
	virtual int MatchedFigsCount(CFigure* fig);
};



#endif
