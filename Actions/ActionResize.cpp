#include "ActionResize.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
#include <iostream>
#include "../Actions/ActionSelect.h"
ActionResize::ActionResize(ApplicationManager* pApp,double _Scale) :Action(pApp)
{
	Scale = _Scale;
	anySelected = false;
}

void ActionResize::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Yasser here");
	int SCount = pManager->GetFigCount();

	////This action needs to read some parameters first
	for (int i = 0; i < SCount; i++){
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
	if (!anySelected) {
		pGUI->PrintMessage("No Figure Selected");
	}

	pGUI->ClearDrawArea();
}

