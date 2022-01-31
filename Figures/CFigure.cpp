#include "CFigure.h"
#include <iostream>

CFigure::CFigure() {}

CFigure::CFigure(GfxInfo FigureGfxInfo,int _FigType)
{ 
	FigGfxInfo = FigureGfxInfo;	// Default status is non-filled.
	Selected = true; // Figure is selected after created
	ID = id++; // Figure ID starts from 1
	FigType = _FigType;
}
////dstructor
CFigure::~CFigure() {
	//ID--;
	std::cout << "from base" << std::endl;
}
//CFigure::Selected = true;
void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

// static value to give Figure ID it's start Value   
int CFigure::id = 1;

// take a copy of pointer obj without Refernce
CFigure* CFigure::CloneFig() 
{
	return NULL;
}


int CFigure::GetCount() {
	return 0;
}


void CFigure::IncCount() { return; }