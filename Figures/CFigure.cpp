#include "CFigure.h"
#include <iostream>

CFigure::CFigure() {}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{
	FigGfxInfo = FigureGfxInfo;	// Default status is non-filled.
	Selected = true; // Figure is selected after created
	ID = id++; // Figure ID starts from 1
}

CFigure::~CFigure(){}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

bool CFigure::IsSelected() const
{
	return Selected;
}

void CFigure::ChngDrawClr(color Dclr)
{
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr;
}

// static value to give Figure ID it's start Value   
int CFigure::id = 1;

int CFigure::GetCount() {
	return 0;
}

void CFigure::IncCount() { return; }

string CFigure::GetFillClr()
{
	if (FigGfxInfo.isFilled)
	{
		color Fillcolor = FigGfxInfo.FillClr;
		if (Fillcolor == TOMATO) return "TOMATO";
		else if (Fillcolor == DEEPSKYBLUE) return "DEEPSKYBLUE";
		else if (Fillcolor == LIGHTGREEN) return "LIGHTGREEN";
		else  return "ORANGE";
	}
	else
		return "NON-FILLED";
}

// figure Name
string CFigure::FigureName() {
	return "Parent";
}
