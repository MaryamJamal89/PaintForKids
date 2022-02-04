#include "ActionResize.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
#include <iostream>
#include "../Actions/ActionSelect.h"
ActionResize::ActionResize(ApplicationManager* pApp) :Action(pApp)
{
	P.x = 0;
	P.y = 0;
	Scale = 0.0;
	anySelected = false;
}

void ActionResize::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->CreateResizeBar();
	pGUI->PrintMessage("Yasser here");
	int SCount = pManager->GetFigCount();

	////This action needs to read some parameters first
	while(ReadActionParameters()){
		for (int i = 0; i < SCount; i++){
			if (Scale != 0) {

				if (pManager->getFigByIndex(i)->IsSelected()) {
					int resize = pManager->getFigByIndex(i)->Resize(Scale);
					if (resize == 0) {
						pGUI->PrintMessage("Figure Resized :"+ pManager->getFigByIndex(i)->FigureName());
					}
					else {
						pGUI->PrintMessage("Can't Resize :" + pManager->getFigByIndex(i)->FigureName());
					}
					
					anySelected = true;
				}
			}
		}
		if (!anySelected) {
			pGUI->PrintMessage("No Figure Selected");
		}

		pGUI->ClearDrawArea();
		pManager->UpdateInterface();
	}
}


bool ActionResize::ReadActionParameters() {

	//Get a Pointer to the Input / Output Interfaces
	GUI* pGUI = pManager->GetGUI();


	/*pGUI->PrintMessage("Resize Figure : Choose The Scale");*/

	//Read Point Parameters

	SCALE = pGUI->MapInputToActionType(P.x, P.y);

	if (!GetScale(SCALE))
	{
		return false;
	}

	pGUI->ClearStatusBar();
	return true;
}

bool ActionResize::GetScale(ActionType S) {    //Convert ActionType to int
	
	Action* ActType = pManager->CreateAction(S);
	int m = 0;
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
		case DRAWING_AREA:
			Scale = 0;
			ActType = NULL;
			ActType = new ActionSelect(pManager, { P.x, P.y }, m);
			pManager->ExecuteAction(ActType);
			return true;
		case TO_DRAW:
			pManager->ExecuteAction(ActType);
			return false;
	}

}

