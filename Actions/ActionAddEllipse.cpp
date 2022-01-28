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

	//Read 1st point and store in point center
	pGUI->PrintMessage("New Ellipse: Click at center point");
	pGUI->GetPointClicked(C.x, C.y);
	CheckPoint(pGUI, C, "New Ellipse: Click at center point");

	//Read 1st point and store in point P1
	pGUI->PrintMessage("New Ellipse: Click at height point");
	pGUI->GetPointClicked(P1.x, P1.y);
	CheckPoint(pGUI, P1, "New Ellipse: Click at height point");

	//Read 2nd point and store in point P2
	pGUI->PrintMessage("New Ellipse: Click at length point");
	pGUI->GetPointClicked(P2.x, P2.y);
	CheckPoint(pGUI, P2, "New Ellipse: Click at length point");

	pGUI->ClearStatusBar();

	//Step 2 - prepare Ellipse data
	//Calcuate ellipse legnth and height
	int SideLength = max(abs(C.x - P1.x), abs(C.y - P1.y));
	int SideHeight = max(abs(C.x - P2.x), abs(C.y - P2.y));

	//Step 3 - Create a Ellipse with the parameters read from the user
	CEllipse* E = new CEllipse(C, SideLength, SideHeight, ElliGfxInfo);

	//and unselect All Previous Figures
	pManager->UnSelectFigures(1);

	//Step 4 - Add the Ellipse to the list of figures
	pManager->AddFigure(E);

	//Step 5 - print new figure info in status bar
	E->PrintInfo(pGUI);
}

void ActionAddEllipse::CheckPoint(GUI* pGUI, Point& point, string mssg)
{
	while (!(point.y >= UI.ToolBarHeight && point.y < UI.height - UI.StatusBarHeight))
	{
		pGUI->PrintTempMessge("You are out of the Drawing Area!!", 2000);
		pGUI->PrintMessage(mssg);
		pGUI->GetPointClicked(point.x, point.y);
	}
}
