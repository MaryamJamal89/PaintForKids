#include "ActionAddSquare.h"

ActionAddSquare::ActionAddSquare(ApplicationManager* pApp) : Action(pApp)
{}

//Execute the action
void ActionAddSquare::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = pGUI->getColorisFilled();  //default is not filled
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	//Step 1 - Read Square data from the user
	//Read 1st point and store in point P1
	pGUI->PrintMessage("New Square: Click at first point");
	pGUI->GetPointClicked(P1.x, P1.y);
	CheckPoint(pGUI, P1, "New Square: Click at first point");

	//Read 2nd point and store in point P2
	pGUI->PrintMessage("New Square: Click at second point");
	pGUI->GetPointClicked(P2.x, P2.y);
	CheckPoint(pGUI, P2, "New Square: Click at second point");

	pGUI->ClearStatusBar();

	//Step 2 - prepare square data
	//User has entered two points P1&P2

	//2.1- Identify the Top left corner of the square
	Point topLeft;
	topLeft.x = P1.x < P2.x ? P1.x : P2.x;
	topLeft.y = P1.y < P2.y ? P1.y : P2.y;

	//2.2- Calcuate square side legnth
	//The square side length would be the longer distance between the two points coordinates
	int SideLength = max(abs(P1.x - P2.x), abs(P1.y - P2.y));

	if ((P1.y + SideLength) < UI.ToolBarHeight || (P2.y + SideLength) >= (UI.height - UI.StatusBarHeight))
	{
		pGUI->PrintTempMessge("Points out of the Drawing Area!", 800);
		return;
	}

	//Step 3 - Create a Square with the parameters read from the user
	CSquare* R = new CSquare(topLeft, SideLength, SqrGfxInfo);

	//and unselect All Previous Figures
	pManager->UnSelectFigures(1);

	//Step 4 - Add the Square to the list of figures
	pManager->AddFigure(R);

	//Step 5 - print new figure info in status bar
	R->PrintInfo(pGUI);
}

void ActionAddSquare::CheckPoint(GUI* pGUI, Point& point, string mssg)
{
	while (!(point.y >= UI.ToolBarHeight && point.y < UI.height - UI.StatusBarHeight))
	{
		pGUI->PrintTempMessge("You are out of the Drawing Area!!", 2000);
		pGUI->PrintMessage(mssg);
		pGUI->GetPointClicked(point.x, point.y);
	}
}