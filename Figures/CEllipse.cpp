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


// InFig return boolian to check point inside Figure 
bool CEllipse::InFig(int x, int y)  //Determine the position of the point
{
	if (pow(x - Center.x, 2) / pow(P.x, 2) + pow(y - Center.y, 2) / pow(P.y, 2) <= 1)
	{
		return true;
	}
	return false;
}

// Print to return all info about figure
string CEllipse::PrintInfo()
{

	string id = to_string(ID);
	string x = to_string(Center.x);
	string y = to_string(Center.y);
	//string clr = getColor(this->FigGfxInfo.DrawClr);

	//if (FigGfxInfo.isFilled)
	//{
	//	//pOut->PrintMessage(" - FillColor: ");
	//	//string clrF = getColor(this->FigGfxInfo.FillClr);
	//	return ("Ellipse -ID: " + id + " Center: (" + x + ", " + y + ") DrawColor:");
	//}
	//else
	return ("Ellipse -ID: " + id + " Center: (" + x + ", " + y + ") DrawColor:");
}