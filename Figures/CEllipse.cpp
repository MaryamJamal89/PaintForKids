#include "CEllipse.h"
#include<fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

int CEllipse::ElliCnt = 0;  //static variable to determine the number of objects

CEllipse::CEllipse(){
	ElliCnt++;
}

CEllipse::CEllipse(Point C, int len, int hght, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = C;
	length = len;
	height = hght;
	ElliCnt++;
}

CEllipse::~CEllipse() {
	ElliCnt--;
	std::cout << "destructor from CEllipse" << std::endl;
}

void CEllipse::DrawMe(GUI* pOut) const
{
	//Call Output::DrawEllipse to draw a ellipse on the screen	
	pOut->DrawEllip(Center, length, height, FigGfxInfo, Selected);
}

// figure Name
string CEllipse::FigureName() {
	return "Ellipse";
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

//loading ellipse from old graph
void CEllipse::Load(ifstream& loadedFile, GUI* pGUI)
{
	string drawColor, fillColor;
	loadedFile >> ID >> Center.x >> Center.y >> length >> height >> drawColor >> fillColor;
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
	if (pow(x - Center.x, 2) / pow(length, 2) + pow(y - Center.y, 2) / pow(height, 2) <= 1)
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
	string len = to_string(length);
	string _height = to_string(height);

	string fillingColor;
	if (FigGfxInfo.isFilled)
	{
		fillingColor = pGUI->ColorToString(FigGfxInfo.FillClr);
	}
	else
	{
		fillingColor = "NO_FILL";
	}
	pGUI->PrintMessage("Ellipse / ID: " + id + " / Center: (" + x + ", " + y + ") / Length: " + len + " / Height: " + _height + " / Drawing Color: " + pGUI->ColorToString(FigGfxInfo.DrawClr) + " / Filling Color: " + fillingColor);
}

// take a copy of pointer obj without Refernce
CEllipse* CEllipse::CloneFig() 
{
	//ElliCnt++;
	return new CEllipse(*this);
}

int CEllipse::GetCount() {
	return ElliCnt;
}

void CEllipse::IncCount() {
	ElliCnt++;
}

int CEllipse::Resize(double scale) {

	//int SideHeight = max(abs(Center.x - P1.x), abs(Center.y - P1.y));
	//int SideLength = max(abs(Center.x - P2.x), abs(Center.y - P2.y));

	//if ((C.y - SideHeight) < UI.ToolBarHeight || (C.y + SideHeight) >= (UI.height - UI.StatusBarHeight))
	//{
	//	//pGUI->PrintTempMessge("Points out of the Drawing Area!", 800);
	//	return;
	//}
	if (!(Center.x + length * scale >= 1300 || Center.x - length * scale <= 0 || Center.y + height * scale >= 650 || Center.y - height * scale <= 50)) {
		if (scale * length >= 20 && scale * height >= 20)
		{
			length = length * scale;
			height = height * scale;
			return 0;
		}
		else if (scale * length <= 20 && scale * height <= 20) {
			return -1;
		}
		else {
			if (scale * length >= 20) {
				length = length * scale;
			}
			else {
				height = height * scale;
			}			
			return 0;
		}
	}

	return 1;
}