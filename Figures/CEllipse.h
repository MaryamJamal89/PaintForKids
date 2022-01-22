#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CFigure.h"

class CEllipse : public CFigure
{
private:
	Point Center, P;

public:
	static int ElliCnt;                      //static variable to determine the number of objects
	CEllipse(Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;  //draw the figure 
};

#endif
#pragma once
