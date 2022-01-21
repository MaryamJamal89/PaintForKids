#ifndef CHEXAGON_H
#define CHEXAGON_H

#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	Point Center, P;

public:
	static int HexCnt;                      //static variable to determine the number of objects
	CHexagon(Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;  //draw the figure 
};

#endif
