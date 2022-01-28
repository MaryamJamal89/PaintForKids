#include "ActionChangeLocation.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

ActionChangeLocation::ActionChangeLocation(ApplicationManager* pApp, bool isFront) : Action(pApp)
{
	this->isFront = isFront;
}

//Execute the action
void ActionChangeLocation::Execute()
{
	pManager->InsertFigure(isFront);
	pManager->UpdateInterface();
}