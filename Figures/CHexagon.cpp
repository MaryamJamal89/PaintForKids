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
	//load
}


