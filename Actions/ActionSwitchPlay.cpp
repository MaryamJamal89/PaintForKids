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
	pGUI->PrintMessage("You are in Play Mode XD");
	// to create New ToolBar
	pGUI->CreatePlayToolBar();
}

