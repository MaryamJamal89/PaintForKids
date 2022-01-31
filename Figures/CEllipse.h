#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CFigure.h"

class CEllipse : public CFigure
{
private:
	Point Center, P;
	int length;
	int height;
	static int ElliCnt;//static variable to determine the number of objects
public:
	 
	CEllipse();
	~CEllipse();
	CEllipse(Point, int, int, GfxInfo FigureGfxInfo);

	virtual void DrawMe(GUI* pOut) const;				// draw the figure 
	virtual void Save(ofstream& file, GUI* pGUI);		// save figure to file
	virtual void Load(ifstream& loadedFile, GUI* pGUI); // load figure from file

	// InFig return boolian to check point inside Figure our Not
	virtual bool InFig(int, int);
	// Print to return all info about figure
	virtual void PrintInfo(GUI* pGUI);
	// take a copy of pointer obj without Refernce
	virtual CEllipse* CloneFig();

	virtual int GetCount();
};

#endif
#pragma once
