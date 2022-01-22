#include "CEllipse.h"

int CEllipse::ElliCnt = 0;  //static variable to determine the number of objects
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
