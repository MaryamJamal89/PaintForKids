#include "ActionDelete.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

ActionDelete::ActionDelete(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionDelete::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	//deleting selected figures
	pManager->DeleteSelectedFigures();
	//clearing the draw area and redraw the figList
	pGUI->ClearDrawArea();
	pManager->UpdateInterface();
	//confirmation message
	pGUI->PrintTempMessge("figures deleted!", 1000);
}
