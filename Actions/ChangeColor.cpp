#include "ChangeColor.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"


ChangeColor::ChangeColor(ApplicationManager* pApp, color c, int drawORfill) : Action(pApp), colour(c), DrawOrFill(drawORfill)
{
}

void ChangeColor::Execute() {


	// Check If The Mode if Change Drawing Color
	if (DrawOrFill == 1) {
		GUI* pGUI = pManager->GetGUI();
		UI.DrawColor = colour;
		pManager->UpdateInterface();
	}
	// Check If The Mode if Change Filling Color
	else if (DrawOrFill == 2) {
		GUI* pGUI = pManager->GetGUI();
		UI.isFilled = true;
		UI.FillColor = colour;
		pManager->UpdateInterface();
	}
	// Check If The Mode if Change background Color
	else if (DrawOrFill == 3) {
		GUI* pGUI = pManager->GetGUI();
		UI.BkGrndColor = colour;
		//update window to change background color
		pGUI->ClearDrawArea();
	}


}