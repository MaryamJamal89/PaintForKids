#ifndef GUI_H
#define GUI_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"

//This class is responsible for Grphical User Interface handling
//All user input and program outputs MUST be done through this class
//No other class is allowed to perform direct i/o
class GUI	
{
public:	
	window* pWind;	//Pointer to the Graphics Window

public:
	GUI();	
	~GUI();	
	window* CreateWind(int, int, int , int) const; //creates the application window

	/////////// Input Functoinality  /////////////////
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting() const ;	 //Returns a string entered by the user
	ActionType MapInputToActionType(int& x, int& y) const; //Read the user click and map to an action

	/////////// Output Functoinality  ////////////////
	void CreateToolBar() const;      //create New Toolbar When Switch From Mode_Draw To Mode_play Edit BY 'Mahmoud' 
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreateDrawColorBar() const; //creates color mode toolbar & menu
	void CreateShapesBar() const;
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	void ClearStatusBar() const;	//Clears the status bar
	void ClearToolBar() const;		//Clears the tool bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected = false) const;	//Draw a Square
	void DrawEllip(Point P1, int length, int height, GfxInfo ElliGfxInfo, bool selected = false) const;		//Draw a Ellipse
	void DrawHex(Point center, int length, GfxInfo HexGfxInfo, bool selected = false) const;	//Draw a Hex
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color StringToColor(string colorStr); //convert string to color type
	string ColorToString(color clr);     //convert color to string
	bool isMatchedColors(color c1, color c2);        //check if two colors are the same
	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	color getBackgroungColor() const;	//get current background color
	bool getColorisFilled() const;
	int getCrntPenWidth() const;		//get current pen width
	
	string ReadFileName(string msg);    //read file name to save or load
	string Confirm(string msg);         //get yes or no response
};

#endif
