#include "ActionPickColor.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionPickColor::ActionPickColor(ApplicationManager* pApp) : Action(pApp)
{}

void ActionPickColor::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	pManager->playType = 2;
	pGUI->PrintMessage("Select Figur To Pick Color-_-!");
}
