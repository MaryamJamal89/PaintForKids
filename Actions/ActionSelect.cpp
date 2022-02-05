#include "ActionSelect.h"
#include <iostream>

using namespace std;

ActionSelect::ActionSelect(ApplicationManager* pApp, Point _P, bool _multiSelect) :Action(pApp)
{
	multiSelect = _multiSelect;
	P = _P;
}

void ActionSelect::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//check where this point :
	//and return selected figure or null 
	CFigure* fig = pManager->GetFigure(P.x, P.y);
	// no figure selected
	if (fig == NULL)
	{
		pGUI->PrintMessage("No Figure Selected");
		pManager->UnSelectFigures(2);
	}
	else
	{
		if (fig->IsSelected())
		{
			fig->SetSelected(false);
			pGUI->ClearStatusBar();
		}
		else
		{
			// IF Multiple select Enabled
			if (!multiSelect)
			{
				pManager->UnSelectFigures(2);
			}
			fig->SetSelected(true);
			fig->PrintInfo(pGUI);
		}
	}
}
