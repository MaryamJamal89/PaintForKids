#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CFigure.h"

class CEllipse : public CFigure
{
private:
	Point Center, P;

public:
	static int ElliCnt;                      //static variable to determine the number of objects
	CEllipse();
	CEllipse(Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;  //draw the figure 
	virtual void Save(ofstream& file, GUI* pGUI);                   // save figure to file
	virtual void Load(ifstream& loadedFile, GUI* pGUI); //load figure from file
};

#endif
#pragma once
