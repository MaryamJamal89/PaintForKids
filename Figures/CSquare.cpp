#include "CSquare.h"
#include<fstream>
#include <iostream>

int CSquare::SqrCnt = 0;  //static variable to determine the number of objects

CSquare::CSquare(){
	SqrCnt++;
}

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
	SqrCnt++;
}



CSquare::~CSquare() {
	SqrCnt--;
	std::cout << "destructor from CSquare" << std::endl;
}

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
}

// figure Name
string CSquare::FigureName(){
	return "Sqaure";
}

// save figure in the file
void CSquare::Save(ofstream& file, GUI* pGUI)
{
	file << "SQR " << ID << " " << TopLeftCorner.x << " " << TopLeftCorner.y << " " << length << " " << pGUI->ColorToString(FigGfxInfo.DrawClr) << " ";
	
	if (FigGfxInfo.isFilled == true)
	{
		file << pGUI->ColorToString(FigGfxInfo.FillClr) << endl;
	}
	else
	{
		file << "NO_FILL" << endl;
	}
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
void CSquare::PrintInfo(GUI* pGUI)
{
	string id = to_string(ID);
	string x1 = to_string(TopLeftCorner.x);
	string y1 = to_string(TopLeftCorner.y);
	string len = to_string(length);
	/*string x2 = to_string(TopLeftCorner.x + length);
	string y2 = to_string(TopLeftCorner.y + length);*/

	string fillingColor;
	if (FigGfxInfo.isFilled)
	{
		fillingColor = pGUI->ColorToString(FigGfxInfo.FillClr);
	}
	else
	{
		fillingColor = "NO_FILL";
	}
	pGUI->PrintMessage("Square / ID:" + id + " / Top Left Corner: (" + x1 + ", " + y1 + ") /" + " Length: " + len +  " / " + " Drawing Color: " + pGUI->ColorToString(FigGfxInfo.DrawClr) + " / Filling Color: " + fillingColor);
}

// take a copy of pointer obj without Refernce
CSquare* CSquare::CloneFig() 
{
	//SqrCnt++;
	return new CSquare(*this);
}


int CSquare::GetCount() {
	return SqrCnt;
}

void CSquare::IncCount() {
	SqrCnt++;
}

// make it return  1 or -1 or 0 
// if 1  size is  very big
// if 0  nothing it will resize 
// if -1 can't resize size is very smal 

int CSquare::Resize(double scale) {	
	if (TopLeftCorner.x + length * scale >= 1300 || TopLeftCorner.y + length * scale >= 650
		|| scale * length <= 20) {
		return 1;
	}
	else {
		length = scale * length;
		return 0;
	}
}