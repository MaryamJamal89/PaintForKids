#include "ActionAddHexagon.h"

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

	//Step 1 - Read Hexagon data from the user
	//Read 1st point and store in point center
	pGUI->PrintMessage("New Hexagon: Click at center point");
	pGUI->GetPointClicked(C.x, C.y);
	CheckPoint(pGUI, C, "New Hexagon: Click at center point");

	//Read 2nd point and store in point P1
	pGUI->PrintMessage("New Hexagon: Click at length point");
	pGUI->GetPointClicked(P1.x, P1.y);
	CheckPoint(pGUI, P1, "New Hexagon: Click at length point");

	pGUI->ClearStatusBar();

	//Step 2 - prepare Hexagon data
	//Calcuate hexagon Side Length
	int SideLength = max(abs(C.x - P1.x), abs(C.y - P1.y));

	int d = SideLength;

	Point point1;
	point1.x = C.x - d;
	point1.y = C.y;
	Point point2;
	point2.x = C.x - d / 2;
	point2.y = C.y - (d - d / 20 * 3);
	Point point3;
	point3.x = C.x + d / 2;
	point3.y = C.y - (d - d / 20 * 3);
	Point point4;
	point4.x = C.x + d;
	point4.y = C.y;
	Point point5;
	point5.x = C.x + d / 2;
	point5.y = C.y + (d - d / 20 * 3);
	Point point6;
	point6.x = C.x - d / 2;
	point6.y = C.y + (d - d / 20 * 3);

	int Xpoints[6] = { point1.x, point2.x, point3.x, point4.x, point5.x, point6.x };
	int Ypoints[6] = { point1.y, point2.y, point3.y, point4.y, point5.y, point6.y };

	for (int i = 0; i < 6; i++)
	{
		if (Ypoints[i] < UI.ToolBarHeight || Ypoints[i] >= (UI.height - UI.StatusBarHeight))
		{
			pGUI->PrintTempMessge("Points out of the Drawing Area!", 800);
			return;
		}
	}

	//Step 3 - Create a Hexagon with the parameters read from the user
	CHexagon* H = new CHexagon(Xpoints, Ypoints, C, SideLength, HexGfxInfo);

	//and unselect All Previous Figures
	pManager->UnSelectFigures(1);

	//Step 4 - Add the Hexagon to the list of figures
	pManager->AddFigure(H);

	//Step 5 - print new figure info in status bar
	H->PrintInfo(pGUI);
}

void ActionAddHexagon::CheckPoint(GUI* pGUI, Point &point, string mssg)
{
	while (!(point.y >= UI.ToolBarHeight && point.y < UI.height - UI.StatusBarHeight))
	{
		pGUI->PrintTempMessge("You are out of the Drawing Area!!", 2000);
		pGUI->PrintMessage(mssg);
		pGUI->GetPointClicked(point.x, point.y);
	} 
}