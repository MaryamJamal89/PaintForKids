#include "ActionPickImage_Color.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
#include <iostream>
#include <string>

ActionPickImage_Color::ActionPickImage_Color(ApplicationManager* pApp) : Action(pApp)
{
	validCounter = 0;
	invalidCounter = 0;
	toolBar = false;
}

// return selected Figure
CFigure* ActionPickImage_Color::ReadesFigures()
{
	Point point;
	GUI* pGUI = pManager->GetGUI();
	pGUI->pWind->WaitMouseClick(point.x, point.y);
	return  pManager->GetFigure(point.x, point.y);
}

void ActionPickImage_Color::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	if (pManager->GetFigCount() == 0)
	{
		pGUI->PrintMessage("Draw some figures to play!");
	}
	else
	{
		Point point;

		// rearange shapes to start game
		// clear Area
		pGUI->ClearDrawArea();
		// take backup
		pManager->TakeFigOfDrawMode();
		// un select all figures 
		pManager->UnSelectFigures(2);
		// draw shapes again
		pManager->UpdateInterface();

		// get Rondom figure
		fig = pManager->GetRandomFigure()->CloneFig();
		// update status Bar
		UpdateStatusBar(fig);
		ActionType pAct;
		bool Matches;
		// if fig not null
		if (fig)
		{
			figCount = MatchedFigsCount(fig);
			while (figCount)
			{
				pAct = pGUI->MapInputToActionType(point.x, point.y);
				if (pAct == RESTART || pAct == TO_PICK_IMAGE || pAct == TO_PICK_COLOR || pAct == TO_PICK_IMAGE_COLOR || pAct == TO_DRAW)
				{
					toolBar = true;
					Action* ActType = pManager->CreateAction(pAct);
					pManager->ExecuteAction(ActType);
					delete ActType;
					break;
				}
				CFigure* selectedFig = pManager->GetFigure(point.x, point.y);
				pManager->UnSelectFigures(2);
				if (selectedFig)
				{
					selectedFig->SetSelected(true);

					// Matchs
					bool Matches = figureMatches(fig, selectedFig);
					if (Matches)
					{
						validCounter++;
						figCount--;
					}
					// not Match
					else
					{
						invalidCounter++;
					}
					string msg = " valid Choises: " + to_string(validCounter) + " invalid Choises: " + to_string(invalidCounter) + "  ";
					pGUI->PrintMessage(msg);
					pManager->DeleteSelectedFigures();
					pGUI->ClearDrawArea();
					pManager->UpdateInterface();
				}
				else
				{
					pGUI->PrintMessage("No Figure Selected");
				}
			}

			// to Clear Area
			pGUI->ClearDrawArea();


			// if user pressed restart 
			if (!toolBar)
			{
				// game over
				pGUI->PrintMessage("Game Over Your valid Choises : " + to_string(validCounter) + " and invalid Choises : " + to_string(invalidCounter));
			}

			toolBar = false;

		}
		// delete random figure pointer
		delete fig;
	}
}

// update status 
void ActionPickImage_Color::UpdateStatusBar(CFigure* fig)
{
	GUI* pGUI = pManager->GetGUI();

	//string figure;
	if (fig)
	{
		pGUI->PrintMessage("Game Started : Choose all " + fig->FigureName() + " with Color " + fig->GetFillClr() + " count: " + to_string(MatchedFigsCount(fig)));
	}
	else
	{
		pGUI->PrintMessage("There are no Figures to play with please draw some Figures or load a file ");
	}
}

//check if figure Matches or not
bool ActionPickImage_Color::figureMatches(CFigure* figure, CFigure* selectedFigure)
{
	if (figure->FigureName().compare(selectedFigure->FigureName()) == 0)
	{
		if (figure->GetFillClr() == selectedFigure->GetFillClr())
		{
			return true;
		}
	}
	return false;
}

// get matched count 
int ActionPickImage_Color::MatchedFigsCount(CFigure* fig)
{
	int count = 0;
	int figCount = pManager->GetFigCount();
	CFigure* figure;

	for (int i = 0; i < figCount; i++)
	{
		figure = pManager->getFigByIndex(i);
		if (figure)
		{
			if (figureMatches(fig, figure))
			{
				count++;
			}
		}
	}
	return count;
}
