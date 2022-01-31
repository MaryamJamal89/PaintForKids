#include "ActionChangeColor.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
#include"../Figures/CFigure.h"

ActionChangeColor::ActionChangeColor(ApplicationManager* pApp, color c, int drawORfill, CFigure* figure) : Action(pApp), colour(c), DrawOrFill(drawORfill), Figure(figure)
{}

void ActionChangeColor::Execute() 
{
	// Check If The Mode if Change Drawing Color
	if (DrawOrFill == 1) {
		if (Figure != NULL)
			Figure->ChngDrawClr(colour);
		else
			UI.DrawColor = colour;

		pManager->UpdateInterface();
	}
	// Check If The Mode if Change Filling Color
	else if (DrawOrFill == 2) {
		if (Figure != NULL)
			Figure->ChngFillClr(colour);
		else {
			UI.isFilled = true;
			UI.FillColor = colour;
		}
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
