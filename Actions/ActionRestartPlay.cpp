#include "ActionRestartPlay.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionRestartPlay::ActionRestartPlay(ApplicationManager* pApp) : Action(pApp)
{}

void ActionRestartPlay::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	// to create New ToolBar

	// to return the figures
	pGUI->ClearDrawArea();

	// restart game also 
	//pManager->TakeFigOfDrawMode();
	pManager->ShowAllFigures();
	pManager->UnSelectFigures(2);
	pManager->UpdateInterface();
	pGUI->PrintTempMessge("Restart Play!", 1000);
}
