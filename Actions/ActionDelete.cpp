#include "ActionDelete.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

ActionDelete::ActionDelete(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionDelete::Execute()
{
	GUI* pGUI = pManager->GetGUI();

	//check if there were any selected figures to delete
	if (pManager->GetFigCount() == 0)
	{
		pGUI->PrintTempMessge("No selected figure(s) to delete!", 1000);
	}
	else
	{
		//deleting selected figures
		pManager->DeleteSelectedFigures();
		//clearing the draw area and redraw the figList
		pGUI->ClearDrawArea();
		pManager->UpdateInterface();
		//confirmation message
		pGUI->PrintTempMessge("figure(s) deleted!", 1000);
	}
}
