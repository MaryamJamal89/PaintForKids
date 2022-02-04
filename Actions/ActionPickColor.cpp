#include "ActionPickColor.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionPickColor::ActionPickColor(ApplicationManager* pApp) : ActionPickImage_Color(pApp)
{}

bool ActionPickColor::figureMatches(CFigure* figure, CFigure* selectedFigure)
{
	if (figure->GetFillClr() == selectedFigure->GetFillClr())
	{
		return true;
	}
	return false;
}

void ActionPickColor::UpdateStatusBar(CFigure* fig)
{
	GUI* pGUI = pManager->GetGUI();

	//string figure;
	if (fig)
	{
		pGUI->PrintMessage("Game Started : Choose all Shapes with Color " + fig->GetFillClr() + " count: " + to_string(MatchedFigsCount(fig)));
	}
	else
	{
		pGUI->PrintMessage("There are no Figures to play with please draw some Figures or load a file ");
	}
}