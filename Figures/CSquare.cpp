#include "CSquare.h"
#include<fstream>

CSquare::CSquare(){}

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
}
	
void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
}

void CSquare::Load(ifstream& loadedFile, GUI* pGUI)
{
	string drawColor, fillColor;
	loadedFile >> ID >> TopLeftCorner.x >> TopLeftCorner.y >> length >> drawColor >> fillColor;
	FigGfxInfo.DrawClr = pGUI->StringToColor(drawColor);
	if (fillColor == "NO_FILL")
	{
		FigGfxInfo.isFilled = false;
	}
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = pGUI->StringToColor(fillColor);
	}
	CSquare::SetSelected(false);
}

// khaled
// check point inside the figure our Not
bool CSquare::InFig(int x, int y)
{
	if ((x >= TopLeftCorner.x && x <= TopLeftCorner.x + length) && (y >= TopLeftCorner.y && y <= TopLeftCorner.y + length))
	{
		return true;
	}
	return false;
}

// to print info about figure in the status bar 
// we have to write info about color 
string CSquare::PrintInfo()
{
	string id = to_string(ID);
	string x1 = to_string(TopLeftCorner.x);
	string y1 = to_string(TopLeftCorner.y);
	string x2 = to_string(TopLeftCorner.x + length);
	string y2 = to_string(TopLeftCorner.y + length);

	return ("Rectangle - ID:" + id + " Corner1: (" + x1 + ", " + y1 + ")" + " Corner2: (" + x2 + ", " + y2 + ")" + " DrawColor: ");
}
