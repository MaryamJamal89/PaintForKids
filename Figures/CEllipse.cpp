#include "CEllipse.h"
#include<fstream>

int CEllipse::ElliCnt = 0;  //static variable to determine the number of objects

CEllipse::CEllipse(){}

CEllipse::CEllipse(Point C, int len, int hght, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = C;
	length = len;
	height = hght;
	ElliCnt++;
}

void CEllipse::DrawMe(GUI* pOut) const
{
	//Call Output::DrawEllipse to draw a ellipse on the screen	
	pOut->DrawEllip(Center, length, height, FigGfxInfo, Selected);
}

//save figure in the file
void CEllipse::Save(ofstream& file, GUI* pGUI)
{
	file << "ELPS " << ID << " " << Center.x << " " << Center.y << " " << length << " "<< height<<" "<< pGUI->ColorToString(FigGfxInfo.DrawClr) << " ";

	if (FigGfxInfo.isFilled == true)
	{
		file << pGUI->ColorToString(FigGfxInfo.FillClr) << endl;
	}
	else
	{
		file << "NO_FILL" << endl;
	}
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
	// (x - Center.x) ^ 2 / h ^ 2 + (y - Center.y) ^ 2 / l ^ 2 <= 1
	if (pow(x - Center.x, 2) / pow(height, 2) + pow(y - Center.y, 2) / pow(length, 2) <= 1)
	{
		return true;
	}
	return false;
}

// Print to return all info about figure
void CEllipse::PrintInfo(GUI* pGUI)
{
	string id = to_string(ID);
	string x = to_string(Center.x);
	string y = to_string(Center.y);

	string fillingColor;
	if (FigGfxInfo.isFilled)
	{
		fillingColor = pGUI->ColorToString(FigGfxInfo.FillClr);
	}
	else
	{
		fillingColor = "NO_FILL";
	}
	pGUI->PrintMessage("Ellipse / ID: " + id + " Center: (" + x + ", " + y + ") / Drawing Color: " + pGUI->ColorToString(FigGfxInfo.DrawClr) + " / Filling Color: " + fillingColor);
}