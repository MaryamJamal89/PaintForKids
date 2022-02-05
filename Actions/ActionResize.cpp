#include "ActionResize.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
#include <iostream>
#include "../Actions/ActionSelect.h"
ActionResize::ActionResize(ApplicationManager* pApp,double _Scale) :Action(pApp)
{
	Scale = _Scale;
	anyFigSelected = false;
}

void ActionResize::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Resize figure - Choose the scale");
	int figuresCount = pManager->GetFigCount();
	int resized;

	for (int i = 0; i < figuresCount; i++){
		if (pManager->getFigByIndex(i)->IsSelected()) {
			resized = pManager->getFigByIndex(i)->Resize(Scale);

			if (resized == 0) {
				pGUI->PrintMessage("Figure Resized :"+ pManager->getFigByIndex(i)->FigureName());
			}
			else {
				pGUI->PrintMessage("Can't Resize :" + pManager->getFigByIndex(i)->FigureName());
			}
			anyFigSelected = true;
		}
	}
	if (!anyFigSelected) {
		pGUI->PrintMessage("No figure selected");
	}

	pGUI->ClearDrawArea();
}