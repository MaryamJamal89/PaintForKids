#include "./ActionAddEllipse.h"
#include "../Figures/CEllipse.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionAddEllipse::ActionAddEllipse(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddEllipse::Execute()
{
	Point C;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	GfxInfo ElliGfxInfo;
	ElliGfxInfo.isFilled = pGUI->getColorisFilled();		//default is not filled
	//get drawing, filling colors and pen width from the interface
	ElliGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	ElliGfxInfo.FillClr = pGUI->getCrntFillColor();
	ElliGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	//Step 1 - Read Ellipse data from the user

	pGUI->PrintMessage("New Ellipse: Click at center point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(C.x, C.y);

	pGUI->ClearStatusBar();

	//Step 2 - Create a Ellipse with the parameters read from the user
	CEllipse* E = new CEllipse(C, ElliGfxInfo);
	
	//and unselect All Previous Figures
	pManager->UnSelectFigures();

	//Step 3 - Add the Ellipse to the list of figures
	pManager->AddFigure(E);
}
