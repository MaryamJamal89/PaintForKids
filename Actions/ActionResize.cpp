#include "ActionResize.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
#include <iostream>
ActionResize::ActionResize(ApplicationManager* pApp) :Action(pApp)
{
	P.x = 0;
	P.y = 0;
	Scale = 0.0;
}

void ActionResize::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	//pGUI->ClearDrawArea();
	pGUI->CreateResizeBar();
	pGUI->PrintMessage("Yasser here");

	////This action needs to read some parameters first
	if (ReadActionParameters())
	{
		GUI* pGUI = pManager->GetGUI();
	int SCount = pManager->GetFigCount();
	//	CFigure* SList = pManager->getSelectedFigures();
	CFigure *selectedFigures[200];
	int selectedCount = 0;
	for (int i = 0; i < SCount; i++)
	{
		if(pManager->getFigByIndex(i)->IsSelected()){
			selectedFigures[i] = pManager->getFigByIndex(i);
			selectedCount++;
		}
	}

		if (selectedFigures[0] != NULL)    //if There was a Selected Figure Resize it 
		{
			for (int i = 0; i < selectedCount; i++){
			selectedFigures[i]->Resize(Scale);

			}

			pGUI->ClearDrawArea();
			pManager->UpdateInterface();
			/*for (int i = 0; i < SCount; i++)
				if (selectedFigures[i]->IsLastSelected())
				{
					SList[i]->printinfo(pGUI);
					break;
				}*/
		}
		else
			pGUI->PrintMessage("Select Figure at First");
	}
}


bool ActionResize::ReadActionParameters() {

	//Get a Pointer to the Input / Output Interfaces
	GUI* pGUI = pManager->GetGUI();


	pGUI->PrintMessage("Resize Figure : Choose The Scale");

	//Read Point Parameters

	SCALE = pGUI->MapInputToActionType(P.x, P.y);
	if (!GetScale(SCALE))
	{
		pGUI->PrintMessage("Invalid Point : Choose Scale Please");
		return false;
	}

	pGUI->ClearStatusBar();
	return true;
}

bool ActionResize::GetScale(ActionType S) {    //Convert ActionType to int
	switch (S)
	{
	case RESIZE_DOUBLE:
		Scale = 2;
		return true;
	case RESIZE_QUADRUPLE:
		Scale = 4;
		return true;
	case RESIZE_HALF:
		Scale = 0.5;
		return true;
	case RESIZE_QUARTER:
		Scale = 0.25;
		return true;
	default:
		return false;
	}

}

