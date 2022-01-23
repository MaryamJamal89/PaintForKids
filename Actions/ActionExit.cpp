#include "ActionExit.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

ActionExit::ActionExit(ApplicationManager* pApp) :Action(pApp)
{}


//Execute the action
void ActionExit::Execute()
{
	//ask user to save first


	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("Do you want save current file (Y/N)?");

	string respond = pGUI->GetSrting();

	while (!(respond == "N" || respond == "n" || respond == "Y" || respond == "y"))
	{
		pGUI->PrintMessage("Please enter (Y/N)?");
		respond = pGUI->GetSrting();
	}
	if (respond == "N" || respond == "n")
	{
		pGUI->PrintMessage("NN");
	}
	else
	{
		//save
		pGUI->PrintMessage("YY");
	}
	
}
