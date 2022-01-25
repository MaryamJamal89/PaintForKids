#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
public:
	CSquare();
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	virtual void DrawMe(GUI* pOut) const;
	virtual void Save(ofstream& file, GUI* pGUI);                   // save figure to file
	virtual void Load(ifstream& loadedFile, GUI* pGUI); //load figure from file
	
	// khaled
	virtual bool InFig(int, int);
	virtual string PrintInfo();

};

#endif