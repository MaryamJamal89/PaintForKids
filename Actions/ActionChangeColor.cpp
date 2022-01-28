#include "ActionChangeColor.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"


ActionChangeColor::ActionChangeColor(ApplicationManager* pApp, color c, int drawORfill) : Action(pApp), colour(c), DrawOrFill(drawORfill)
{
}

void ActionChangeColor::Execute() {

	
	// Check If The Mode if Change Drawing Color
	if (DrawOrFill == 1) {
		UI.DrawColor = colour;
		pManager->UpdateInterface();
	}
	// Check If The Mode if Change Filling Color
	else if (DrawOrFill == 2) {
		UI.isFilled = true;
		UI.FillColor = colour;
		pManager->UpdateInterface();
	}
	// Check If The Mode if Change background Color
	else if (DrawOrFill == 3) {
		GUI* pGUI = pManager->GetGUI();
		UI.BkGrndColor = colour;
		pGUI->ClearDrawArea();
		pManager->UpdateInterface();
	}


}