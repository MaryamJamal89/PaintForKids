#include "ActionSelect.h"
#include <iostream>



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

	pGUI->PrintMessage("No Figure Selected");
	
	// no figure selected
	if (fig == NULL) {
		pManager->UnSelectFigures();
	}
	else
	{
		if (fig->IsSelected()) 
		{
			fig->SetSelected(false);
		}
		else
		{
			// Enabling Multiple select
			if (!multiSelect) 
			{
				pManager->UnSelectFigures();
			}
			fig->SetSelected(true);
			fig->PrintInfo(pGUI);
		}
	}
}