#include "GUI.h"

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	//UI.InterfaceMode = MODE_DRAW;
	
	//UI.width = 1300;
	//UI.height = 700;
	//UI.wx = 5;
	//UI.wy = 5;
	
	//UI.StatusBarHeight = 50;
	//UI.ToolBarHeight = 50;
	//UI.MenuItemWidth = 80;
	
	//UI.DrawColor = BLUE;	//Drawing color
	//UI.FillColor = GREEN;	//Filling color
	//UI.MsgColor = RED;		//Messages color
	//UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	//UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	//UI.StatusBarColor = TURQUOISE;
	//UI.PenWidth = 3;	//width of the figures frames

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);

	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}

//======================================================================================//
//								Input Functions										    //
//======================================================================================//

void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

bool GUI::getColorisFilled() const {

	return UI.isFilled;
}

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType(int &x,int &y) const
{	
	//int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SHAPES: return DRAW_SHAPES;
			case ITM_MULSELECT: return MUL_SELECT;
			case ITM_BACK: return SEND_BACK;
			case ITM_FRONT: return BRNG_FRNT;
			case ITM_DROWCLR: return CHNG_DRAW_CLR;
			case ITM_FILLCLR: return CHNG_FILL_CLR;
			case ITM_BGCLR: return CHNG_BK_CLR;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_PLAY: return TO_PLAY;
			case ITM_EXIT: return EXIT;
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_COLOR) {
		int ClickedItemOrder = (x / UI.MenuItemWidth);

		switch (ClickedItemOrder)
		{
		case ITM_RED: return COLOR_RED;
		case ITM_BLUE: return COLOR_BLUE;
		case ITM_GREEN: return COLOR_GREEN;
		}
	}
	else if (UI.InterfaceMode == MODE_SHAPES) {
		int ClickedItemOrder = (x / UI.MenuItemWidth);
		switch (ClickedItemOrder)
		{
		case ITM_SQUR: return DRAW_SQUARE;
		case ITM_ELPS: return DRAW_ELPS;
		case ITM_HEX: return DRAW_HEX;
		}
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		//return TO_PLAY;	//just for now. This should be updated
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_PICK_IMAGE: return TO_PICK_IMAGE;
			case ITM_PICK_FILL_COLOR: return TO_PICK_COLOR;
			case ITM_PICK_IMAGE_COLOR: return TO_PICK_IMAGE_COLOR;
			case ITM_DRAW: return TO_DRAW;


			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

	}

}

//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearToolBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle( 0, 0 , UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateDrawToolBar() const
{
	//ClearDrawArea();
	CreateToolBar();
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SHAPES] = "images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_MULSELECT] = "images\\MenuItems\\Menu_MultiSelect.jpg";
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\Menu_Back.jpg";
	MenuItemImages[ITM_FRONT] = "images\\MenuItems\\Menu_Front.jpg";
	MenuItemImages[ITM_DROWCLR] = "images\\MenuItems\\Menu_ChangeColor.jpg";
	MenuItemImages[ITM_FILLCLR] = "images\\MenuItems\\Menu_FillColor.jpg";
	MenuItemImages[ITM_BGCLR] = "images\\MenuItems\\Menu_BGColor.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\MenuSave.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[ITM_PLAY] = "images\\MenuItems\\Menu_Switch2.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateShapesBar() const {

	UI.InterfaceMode = MODE_SHAPES;

	string DrawShapesItem[Shapes_COUNT];

	DrawShapesItem[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	DrawShapesItem[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	DrawShapesItem[ITM_HEX] = "images\\MenuItems\\Menu_Hex.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < Shapes_COUNT; i++)
		pWind->DrawImage(DrawShapesItem[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateDrawColorBar() const {

	UI.InterfaceMode = MODE_COLOR;

	string DrawColorItem[Color_COUNT];
	DrawColorItem[ITM_RED] = "images\\MenuItems\\Menu_Red.jpg";
	DrawColorItem[ITM_BLUE] = "images\\MenuItems\\Menu_Blue.jpg";
	DrawColorItem[ITM_GREEN] = "images\\MenuItems\\Menu_Green.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < Color_COUNT; i++)
		pWind->DrawImage(DrawColorItem[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	ClearDrawArea();
	CreateToolBar();
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_PICK_IMAGE] = "images\\MenuItems\\Pick_Image.jpg";
	MenuItemImages[ITM_PICK_FILL_COLOR] = "images\\MenuItems\\Pick_Color.jpg";
	MenuItemImages[ITM_PICK_IMAGE_COLOR] = "images\\MenuItems\\Pick_All.jpg";
	MenuItemImages[ITM_DRAW] = "images\\MenuItems\\Menu_Switch2.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);	
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}

//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}

//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}

//////////////////////////////////////////////////////////////////////////////////////////
color GUI::getBackgroungColor() const	//get current background color
{
	return UI.BkGrndColor;
}
//////////////////////////////////////////////////////////////////////////////////////////
	
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

/// //////////////////////////////////////////////////////////////////////////////////////

color GUI::StringToColor(string colorStr)    //convert string to color type
{
	if (colorStr == "BLUE") return BLUE;
	else if (colorStr == "BLACK") return BLACK;
	else if (colorStr == "RED") return RED;
	else if (colorStr == "YELLOW") return YELLOW;
	else if (colorStr == "WHITE") return WHITE;
	else if (colorStr == "GREEN") return GREEN;
	else if (colorStr == "ORANGE") return ORANGE;
}
////////////////////////////////////////////////////////////////////  covert color to  string
string GUI::ColorToString(color clr)    //convert string to color type
{
	if (isMatchedColors(clr,BLUE)) return "BLUE";
	else if (isMatchedColors(clr,BLACK)) return "BLACK";
	else if (isMatchedColors(clr, RED)) return "RED";
	else if (isMatchedColors(clr,YELLOW)) return "YELLOW";
	else if (isMatchedColors(clr, WHITE)) return "WHITE";
	else if (isMatchedColors(clr, GREEN)) return "GREEN";
	else if (isMatchedColors(clr, ORANGE)) return "ORANGE";
	else if (isMatchedColors(clr, LIGHTGOLDENRODYELLOW)) return "LIGHTGOLDENRODYELLOW";	
}

bool GUI::isMatchedColors(color c1, color c2)      //check if two color objects are matched
{
	if (c1.ucBlue == c2.ucBlue && c1.ucRed == c2.ucRed && c1.ucGreen == c2.ucGreen)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P1.x + length, P1.y + length, style);
	//pWind->DrawLine(P1.x, P1.y, P1.x + length, P1.y + length, style);
}

void GUI::DrawEllip(Point center, int length, int height, GfxInfo ElliGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = ElliGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 3);
	drawstyle style;
	if (ElliGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(ElliGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawEllipse(center.x - height, center.y - length, center.x + height, center.y + length, style);
}

void GUI::DrawHex(Point center, int length, GfxInfo HexGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 3);
	drawstyle style;
	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int d = length;

	Point point1;
	point1.x = center.x - d;
	point1.y = center.y;
	Point point2;
	point2.x = center.x - d / 2;
	point2.y = center.y - (d - d / 20 * 3);
	Point point3;
	point3.x = center.x + d / 2;
	point3.y = center.y - (d - d / 20 * 3);
	Point point4;
	point4.x = center.x + d;
	point4.y = center.y;
	Point point5;
	point5.x = center.x + d / 2;
	point5.y = center.y + (d - d / 20 * 3);
	Point point6;
	point6.x = center.x - d / 2;
	point6.y = center.y + (d - d / 20 * 3);

	int Xpoints[6] = { point1.x, point2.x, point3.x, point4.x, point5.x, point6.x };
	int Ypoints[6] = { point1.y, point2.y, point3.y, point4.y, point5.y, point6.y };

	// Draw the polygon.
	pWind->DrawPolygon(Xpoints, Ypoints, 6, style);
}

//////////////////////////////////////////////////////////////////////////////////////////

string GUI::ReadFileName(string msg)       //read file name to save or load
{
	PrintMessage(msg);
	return GetSrting();
}

string GUI::Confirm(string msg)          //get yes or no response
{
	PrintMessage(msg);

	string response;
	do {
		response = GetSrting();
		PrintMessage("Please enter (Y/N)?");
	} while (!(response == "N" || response == "n" || response == "Y" || response == "y"));

	return response;
}

//////////////////////////////////////////

GUI::~GUI()
{
	delete pWind;
}
