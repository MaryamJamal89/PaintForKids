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

// save figure in the file
void CSquare::Save(ofstream& file, GUI* pGUI)
{
	file << "SQR " << ID << " " << TopLeftCorner.x << " " << TopLeftCorner.y << " " << length << " " << pGUI->ColorToString(FigGfxInfo.DrawClr) << "  " << pGUI->ColorToString(FigGfxInfo.FillClr) << endl;
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
