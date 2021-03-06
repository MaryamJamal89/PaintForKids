#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_COLOR,
	MODE_SHAPES,
	MODE_RESIZE,
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SHAPES,		//Square item in menu

	ITM_DROWCLR,
	ITM_FILLCLR,
	ITM_BGCLR,

	ITM_BACK,
	ITM_FRONT,

	ITM_MULSELECT,   //button for multiselection
	ITM_DEL,
	
	ITM_SAVE,       //save item
	ITM_LOAD,       //Load item
	ITM_RESIZE,
	ITM_PLAY,       //Switch Play Item Edit By 'Mahmoud'
	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
};

enum ShapesItem //The items of the Draw menu (you should add more items)
{
	ITM_SQUR,		//Square item in menu
	ITM_ELPS,		//Ellipse item in menu
	ITM_HEX,		//Hex item in menu
	ITM_SHAPESBACK,

	Shapes_COUNT
};

enum DrawColorItem //The items of the Draw menu (you should add more items)
{
	ITM_TOMATO,
	ITM_DEEPSKYBLUE,
	ITM_LIGHTGREEN,
	ITM_ORANGE,
	ITM_COLORBACK,

	Color_COUNT
};
enum DrawResizeItems
{
	ITM_QUARTER,
	ITM_HALF,
	ITM_DOUBLE,
	ITM_QUADRUPLE,
	ITM_RESIZEBACK,

	ITEMS_COUNT
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	ITM_PICK_IMAGE,			//Pick Item Edit By 'Mahmoud'
	ITM_PICK_FILL_COLOR,	//Pick Fill Color Edit By 'Mahmoud'
	ITM_PICK_IMAGE_COLOR,   //Pick Item And Color Edit By 'Mahmoud'
	ITM_RESTART,			//Restart Play Edit By 'Mahmoud'
	ITM_DRAW,				//Switch Draw Item Edit By 'Mahmoud'
	PLAY_ITM_COUNT			//no. of menu items ==> This should be the last line in this enum
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
	
	bool isFilled = false;      //current filling status of upcoming figures

	color DrawColor = DEEPSKYBLUE;			//Drawing color
	color FillColor = LIGHTGREEN;		//Filling color
	color HighlightColor = MAGENTA;	//Highlighting color
	color MsgColor = DARKRED;			//Messages color
	color BkGrndColor = MYTHISTLE;		//Background color
	color ToolBarColor = WHITE;			//ToolBarColor
	color StatusBarColor = MYDARKGRAY;	//Status bar color
	int PenWidth = 3;				//width of the pen that draws shapes

}UI;	//create a global object UI

#endif