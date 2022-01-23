#ifndef CHEXAGON_H
#define CHEXAGON_H

#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	Point Center, P;

public:
	static int HexCnt;                      //static variable to determine the number of objects
	CHexagon();
	CHexagon(Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;  //draw the figure 
	virtual void Save(ofstream& file);                   // save figure to file
	virtual void Load(ifstream& loadedFile, GUI* pGUI); //load figure from file
};

#endif
