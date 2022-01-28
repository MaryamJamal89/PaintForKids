#include "ActionSwitchPlay.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionSwitchPlay::ActionSwitchPlay(ApplicationManager* pApp) :Action(pApp)
{
}
void ActionSwitchPlay::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	// to create New ToolBar
	pGUI->CreatePlayToolBar();
	pGUI->PrintTempMessge("Welcome to Play mode!", 1000);
	// to take a copy of the original array
	pManager->TakeCopyOfFigures();
	pManager->multiSelect = 0;
	pManager->UnSelectFigures(2);
}

