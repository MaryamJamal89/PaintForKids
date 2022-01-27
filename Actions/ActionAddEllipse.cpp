#include "./ActionAddEllipse.h"
#include "../Figures/CEllipse.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionAddEllipse::ActionAddEllipse(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddEllipse::Execute()
{
	Point C, P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	GfxInfo ElliGfxInfo;
	ElliGfxInfo.isFilled = pGUI->getColorisFilled();		//default is not filled
	//get drawing, filling colors and pen width from the interface
	ElliGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	ElliGfxInfo.FillClr = pGUI->getCrntFillColor();
	ElliGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	do
	{
		//Read 1st point and store in point P1
		pGUI->GetPointClicked(C.x, C.y);
		//Read 1st point and store in point P1
		pGUI->GetPointClicked(P1.x, P1.y);

		//Read 2nd point and store in point P2
		pGUI->GetPointClicked(P2.x, P2.y);

		pGUI->PrintMessage("You Clicked In Tool Bar!!");

	} while (P2.y >= 0 && P2.y < UI.ToolBarHeight || P1.y >= 0 && P1.y < UI.ToolBarHeight || C.y >= 0 && C.y < UI.ToolBarHeight);

	pGUI->PrintMessage("New Ellipse");


	pGUI->ClearStatusBar();

	//Step 2 - prepare Ellipse data
	//Calcuate ellipse legnth and height
	int SideLength = max(abs(C.x - P1.x), abs(C.y - P1.y));
	int SideHeight = max(abs(C.x - P2.x), abs(C.y - P2.y));

	//Step 3 - Create a Ellipse with the parameters read from the user
	CEllipse* E = new CEllipse(C, SideLength, SideHeight, ElliGfxInfo);
	
	//and unselect All Previous Figures
	if(!pManager->multiSelect){
		pManager->UnSelectFigures();
	}
	//Step 4 - Add the Ellipse to the list of figures
	pManager->AddFigure(E);

	//Step 5 - print new figure info in status bar
	E->PrintInfo(pGUI);
}