#include "CHexagon.h"
#include<fstream>

int CHexagon::HexCnt = 0;  //static variable to determine the number of objects

CHexagon::CHexagon(){}

CHexagon::CHexagon(Point C, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = C;
	HexCnt++;
	P.x = 80; P.y = 30;
}

void CHexagon::DrawMe(GUI* pOut) const
{
	//Call Output::DrawEllipse to draw a ellipse on the screen	
	pOut->DrawHex(Center, FigGfxInfo, Selected);
}

void CHexagon::Load(ifstream& loadedFile, GUI* pGUI)
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
	CHexagon::SetSelected(false);
}


