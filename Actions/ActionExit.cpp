#include "ActionExit.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "ActionSave.h"

ActionExit::ActionExit(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionExit::Execute()
{
	GUI* pGUI = pManager->GetGUI();

	//ask user to save first
	string response = pGUI->Confirm("Do you want save current file (Y/N)?");
	if (response == "Y" || response == "y")
	{
		//save
		Action* save = new ActionSave(pManager);
		save->Execute();
	}
}

