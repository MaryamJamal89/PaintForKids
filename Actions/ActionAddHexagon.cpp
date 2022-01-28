#include "ActionAddHexagon.h"
#include "../Figures/CHexagon.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionAddHexagon::ActionAddHexagon(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddHexagon::Execute()
{
	Point C, P1;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	GfxInfo HexGfxInfo;
	HexGfxInfo.isFilled = pGUI->getColorisFilled();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	HexGfxInfo.FillClr = pGUI->getCrntFillColor();
	HexGfxInfo.BorderWdth = pGUI->getCrntPenWidth();
	
	do  {
		//Step 1 - Read Hexagon data from the user
		//Read 1st point and store in point center
		pGUI->PrintMessage("New Hexagon: Click at center point");
		pGUI->GetPointClicked(C.x, C.y);

		//Read 2nd point and store in point P1
		pGUI->PrintMessage("New Hexagon: Click at length point");
		pGUI->GetPointClicked(P1.x, P1.y);

		pGUI->PrintMessage("You Clicked In Tool Bar!!");

	}while (C.y >= 0 && C.y < UI.ToolBarHeight || P1.y >= 0 && P1.y < UI.ToolBarHeight);
	

	pGUI->PrintMessage("New Hexagon");

	pGUI->ClearStatusBar();

	//Step 2 - prepare Ellipse data
	//Calcuate hexagon Side Length
	int SideLength = max(abs(C.x - P1.x), abs(C.y - P1.y));

	//Step 3 - Create a Hexagon with the parameters read from the user
	CHexagon* H = new CHexagon(C, SideLength, HexGfxInfo);
	
	//and unselect All Previous Figures
	pManager->UnSelectFigures(1);
	//Step 4 - Add the Hexagon to the list of figures
	pManager->AddFigure(H);

	//Step 5 - print new figure info in status bar
	H->PrintInfo(pGUI);
}