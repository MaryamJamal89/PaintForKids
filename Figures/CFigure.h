#ifndef CFIGURE_H
#define CFIGURE_H

#include <fstream>
#include "..\defs.h"
#include "..\GUI\GUI.h"

//Base class for all figures
class CFigure
{
protected:
	int ID;				//Each figure has an ID
	int static id;
	bool Selected;		//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	
	// Add more parameters if needed.

public:
	CFigure();
	CFigure(GfxInfo FigureGfxInfo);
	void SetSelected(bool );	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	virtual void DrawMe(GUI*) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	

	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	//virtual void Move() = 0;		//Move the figure

	virtual void Save(ofstream &OutFile, GUI* pGUI) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream& loadedFile, GUI* pGUI) = 0;	//Load the figure parameters to the file

	virtual bool InFig(int, int) = 0;		//Determine the position of the Point
	virtual void PrintInfo(GUI* pGUI) = 0; //print all figure info on the status bar
	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif