#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;

public:
	static int SqrCnt;
	CSquare();
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	virtual void DrawMe(GUI* pOut) const;
	virtual void Save(ofstream& file, GUI* pGUI);       // save figure to file
	virtual void Load(ifstream& loadedFile, GUI* pGUI); // load figure from file
	
	virtual bool InFig(int, int);
	virtual void PrintInfo(GUI* pGUI);
};

#endif