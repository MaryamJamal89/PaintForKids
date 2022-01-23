#include "CEllipse.h"
#include<fstream>

int CEllipse::ElliCnt = 0;  //static variable to determine the number of objects

CEllipse::CEllipse(){}

CEllipse::CEllipse(Point C, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = C;
	ElliCnt++;
	P.x = 80; P.y = 30;
}

void CEllipse::DrawMe(GUI* pOut) const
{
	//Call Output::DrawEllipse to draw a ellipse on the screen	
	pOut->DrawEllip(Center, P, FigGfxInfo, Selected);
}

// save figure in the file
void CEllipse::Save(ofstream& file)
{
	//file << "Square " << ID << "  " << TopLeftCorner.x << "  " << TopLeftCorner.y << "  " << length << "  " << endl;
	// << FigGfxInfo.DrawClr << "  " << FigGfxInfo.FillClr << endl;
}

void CEllipse::Load(ifstream& loadedFile, GUI* pGUI)
{
	string drawColor, fillColor;
	loadedFile >> ID >> Center.x >> Center.y >> P.x >> P.y >> drawColor >> fillColor;
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
	CEllipse::SetSelected(false);
}
