#include "ActionPickImage.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionPickImage::ActionPickImage(ApplicationManager* pApp) :Action(pApp)
{
}

void ActionPickImage::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Select Figur-_-!");
}
