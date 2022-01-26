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
	pGUI->PrintMessage("Weeeeeelllllllccccoooomee In Play Mode-_-!");
	// to create New ToolBar
	pGUI->CreatePlayToolBar();
	
}

