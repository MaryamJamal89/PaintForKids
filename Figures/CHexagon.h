#ifndef CHEXAGON_H
#define CHEXAGON_H

#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	Point Center, P;
	int length;
	int* Xpoints = new int[6];
	int* Ypoints = new int[6];
	static int HexCnt;//static variable to determine the number of objects

public:								
	CHexagon();
	virtual ~CHexagon();
	CHexagon(int*, int*, Point, int, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;				//draw the figure 
	virtual void Save(ofstream& file, GUI* pGUI);		// save figure to file
	virtual void Load(ifstream& loadedFile, GUI* pGUI); //load figure from file
	
	// InFig return boolian to check point inside Figure our Not
	virtual bool InFig(int, int);
	// PrintInfo to return all info about figure
	virtual void PrintInfo(GUI* pGUI);

	virtual bool onSegment(Point p, Point q, Point r);
	virtual int orientation(Point p, Point q, Point r);
	virtual bool doIntersect(Point p1, Point q1, Point p2, Point q2);
	virtual bool isInside(Point polygon[], int n, Point p);

	// take a copy of pointer obj without Refernce
	virtual CHexagon* CloneFig();

	virtual int GetCount();
	virtual void IncCount();

	// return Figure Name
	virtual string FigureName();
};

#endif
