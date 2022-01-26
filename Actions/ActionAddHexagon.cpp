#include "ActionAddHexagon.h"
#include "../Figures/CHexagon.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionAddHexagon::ActionAddHexagon(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddHexagon::Execute()
{
	Point C;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	GfxInfo HexGfxInfo;
	HexGfxInfo.isFilled = pGUI->getColorisFilled();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	HexGfxInfo.FillClr = pGUI->getCrntFillColor();
	HexGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	//Step 1 - Read Ellipse data from the user
	pGUI->PrintMessage("New Ellipse: Click at center point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(C.x, C.y);
	pGUI->ClearStatusBar();

	//Step 2 - Create a Ellipse with the parameters read from the user
	CHexagon* H = new CHexagon(C, HexGfxInfo);
	
	//and unselect All Previous Figures
	if (!pManager->multiSelect) {
		pManager->UnSelectFigures();
	}
	//Step 3 - Add the Ellipse to the list of figures
	pManager->AddFigure(H);

	//Step 5 - print new figure info in status bar
	H->PrintInfo(pGUI);
}