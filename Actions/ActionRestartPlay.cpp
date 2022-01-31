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
	pGUI->CreatePlayToolBar();
	// to return the figures
	pManager->TakeFigOfDrawMode();
	pGUI->PrintTempMessge("Restart Play!", 1000);
}
