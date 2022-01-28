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
}

