#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SQUR,		//Square item in menu
	ITM_ELPS,		//Ellipse item in menu
	ITM_HEX,		//Hex item in menu
	
	//TODO: Add more items names here
	ITM_LOAD,       //Load item
	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	//TODO: Add more items names here

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
};

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode = MODE_DRAW;

	int	width = 1300;
	int height = 700;	//Window width and height
	int wx = 5;
	int wy = 5;		//Window starting coordinates
	int StatusBarHeight = 50;	//Status Bar Height
	int ToolBarHeight = 50;		//Tool Bar Height (distance from top of window to bottom line of toolbar)
	int MenuItemWidth = 80;		//Width of each item in toolbar menu


	color DrawColor = BLUE;		//Drawing color
	color FillColor = GREEN;		//Filling color
	color HighlightColor = MAGENTA;	//Highlighting color
	color MsgColor = RED;			//Messages color
	color BkGrndColor = LIGHTGOLDENRODYELLOW;		//Background color
	color StatusBarColor = TURQUOISE;	//Status bar color
	int PenWidth = 3;			//width of the pen that draws shapes

	/// Add more members if needed

}UI;	//create a global object UI

#endif