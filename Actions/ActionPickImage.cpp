#include "ActionPickImage.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionPickImage::ActionPickImage(ApplicationManager* pApp) : ActionPickImage_Color(pApp)
{
}


bool ActionPickImage::figureMatches(CFigure* figure, CFigure* selectedFigure)
{
	if (figure->FigureName() == selectedFigure->FigureName())
	{
		return true;
	}
	return false;
}

void ActionPickImage::UpdateStatusBar(CFigure* fig)
{
	GUI* pGUI = pManager->GetGUI();

	//string figure;
	if (fig)
	{
		pGUI->PrintMessage("Game Started : Choose all  " + fig->FigureName() + " count: " + to_string(MatchedFigsCount(fig)));
	}
	else
	{
		pGUI->PrintMessage("There are no Figures to play with please draw some Figures or load a file ");
	}
}
