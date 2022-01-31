#include "ActionPickImage_Color.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionPickImage_Color::ActionPickImage_Color(ApplicationManager* pApp) : Action(pApp)
{} 

void ActionPickImage_Color::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	pManager->playType = 3;
	pGUI->PrintMessage("Select Figur To Pick Image AND Color-_-!");
}
