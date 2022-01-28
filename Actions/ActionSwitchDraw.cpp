#include "ActionSwitchDraw.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionSwitchDraw::ActionSwitchDraw(ApplicationManager* pApp) : Action(pApp)
{}

void ActionSwitchDraw::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	// to create New ToolBar
	pGUI->CreateDrawToolBar();
	// to return the figures
	pManager->TakeCopyOfFigures();
	pGUI->PrintTempMessge("Welcome to Draw mode!", 1000);
}
