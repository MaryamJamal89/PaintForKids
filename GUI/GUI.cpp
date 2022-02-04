#include "GUI.h"

//constructor make necessary initializations
GUI::GUI()
{
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);

	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();

	PrintTempMessge("Welcome to Draw mode!", 1000);
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
				case ITM_DEL: return DEL;
				case ITM_BACK: return SEND_BACK;
				case ITM_FRONT: return BRNG_FRNT;
				case ITM_DROWCLR: return CHNG_DRAW_CLR;
				case ITM_FILLCLR: return CHNG_FILL_CLR;
				case ITM_BGCLR: return CHNG_BK_CLR;
				case ITM_RESIZE: return RESIZE;
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
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
				case ITM_TOMATO: return COLOR_TOMATO;
				case ITM_DEEPSKYBLUE: return COLOR_DEEPSKYBLUE;
				case ITM_LIGHTGREEN: return COLOR_LIGHTGREEN;
				case ITM_ORANGE: return COLOR_ORANGE;
				case ITM_COLORBACK: return TO_DRAW;
			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}
	}
	else if (UI.InterfaceMode == MODE_SHAPES) {
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
				case ITM_SQUR: return DRAW_SQUARE;
				case ITM_ELPS: return DRAW_ELPS;
				case ITM_HEX: return DRAW_HEX;
				case ITM_SHAPESBACK: return TO_DRAW;
			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}
	}
	else if (UI.InterfaceMode == MODE_RESIZE)
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
				case ITM_QUARTER: return RESIZE_QUARTER;
				case ITM_HALF: return RESIZE_HALF;
				case ITM_DOUBLE: return RESIZE_DOUBLE;
				case ITM_QUADRUPLE: return RESIZE_QUADRUPLE;
				case ITM_RESIZEBACK: return TO_DRAW;
			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
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
				case ITM_RESTART: return RESTART;
				case ITM_DRAW: return TO_DRAW;

				default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
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

void GUI::PrintTempMessge(string msg, int ms) const
{
	PrintMessage(msg);
	Sleep(ms);
	ClearStatusBar();
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
	MenuItemImages[ITM_SHAPES] = "images\\MenuItems\\\shapesMenu\\shapes-color.jpg";
	MenuItemImages[ITM_DROWCLR] = "images\\MenuItems\\draw-color.jpg";
	MenuItemImages[ITM_FILLCLR] = "images\\MenuItems\\fillingColor-color.jpg";
	MenuItemImages[ITM_BGCLR] = "images\\MenuItems\\BGcolor-color.jpg";
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\sendback-color.jpg";
	MenuItemImages[ITM_FRONT] = "images\\MenuItems\\bringfront-color.jpg";
	MenuItemImages[ITM_MULSELECT] = "images\\MenuItems\\multiselect-color.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\delete-color.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\save-color.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\load-color.jpg";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\load-color.jpg";
	MenuItemImages[ITM_PLAY] = "images\\MenuItems\\playmood4-color.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\exit-color.jpg";

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(MYDARKBLACK, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateShapesBar() const {

	UI.InterfaceMode = MODE_SHAPES;

	string DrawShapesItem[Shapes_COUNT];

	DrawShapesItem[ITM_SQUR] = "images\\MenuItems\\shapesMenu\\square-color.jpg";
	DrawShapesItem[ITM_ELPS] = "images\\MenuItems\\shapesMenu\\ellipse-color.jpg";
	DrawShapesItem[ITM_HEX] = "images\\MenuItems\\shapesMenu\\hexagon-color.jpg";
	DrawShapesItem[ITM_SHAPESBACK] = "images\\MenuItems\\return-color.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < Shapes_COUNT; i++)
		pWind->DrawImage(DrawShapesItem[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	pWind->SetPen(MYDARKBLACK, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateResizeBar() const {
	CreateToolBar();
	UI.InterfaceMode = MODE_RESIZE;

	string DrawResizeItem[ITEMS_COUNT];

	DrawResizeItem[ITM_QUARTER] = "images\\MenuItems\\quarter.jpg";
	DrawResizeItem[ITM_HALF] = "images\\MenuItems\\half.jpg";
	DrawResizeItem[ITM_DOUBLE] = "images\\MenuItems\\double.jpg";
	DrawResizeItem[ITM_QUADRUPLE] = "images\\MenuItems\\quadruple.jpg";
	DrawResizeItem[ITM_RESIZEBACK] = "images\\MenuItems\\return-color.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < ITEMS_COUNT; i++)
		pWind->DrawImage(DrawResizeItem[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	pWind->SetPen(MYDARKBLACK, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateDrawColorBar() const {

	UI.InterfaceMode = MODE_COLOR;

	string DrawColorItem[Color_COUNT];
	DrawColorItem[ITM_TOMATO] = "images\\MenuItems\\colorMenu\\TOMATO.jpg";
	DrawColorItem[ITM_DEEPSKYBLUE] = "images\\MenuItems\\colorMenu\\DEEPSKYBLUE.jpg";
	DrawColorItem[ITM_LIGHTGREEN] = "images\\MenuItems\\colorMenu\\LIGHTGREEN.jpg";
	DrawColorItem[ITM_ORANGE] = "images\\MenuItems\\colorMenu\\ORANGE.jpg";
	DrawColorItem[ITM_COLORBACK] = "images\\MenuItems\\return-color.jpg";


	//Draw menu item one image at a time
	for (int i = 0; i < Color_COUNT; i++)
		pWind->DrawImage(DrawColorItem[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	pWind->SetPen(MYDARKBLACK, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	ClearDrawArea();
	CreateToolBar();
	UI.InterfaceMode = MODE_PLAY;
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_PICK_IMAGE] = "images\\MenuItems\\selectShape-color.jpg";
	MenuItemImages[ITM_PICK_FILL_COLOR] = "images\\MenuItems\\selectColor-color.jpg";
	MenuItemImages[ITM_PICK_IMAGE_COLOR] = "images\\MenuItems\\selectAll-color.jpg";
	MenuItemImages[ITM_RESTART] = "images\\MenuItems\\restart.jpg",
	MenuItemImages[ITM_DRAW] = "images\\MenuItems\\return-color.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(MYDARKBLACK, 3);
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
	if (colorStr == "DEEPSKYBLUE") return DEEPSKYBLUE;
	else if (colorStr == "TOMATO") return TOMATO;
	else if (colorStr == "LIGHTGREEN") return LIGHTGREEN;
	else if (colorStr == "ORANGE") return ORANGE;
	else if (colorStr == "BLACK") return BLACK;
	else if (colorStr == "MYDARKBLACK") return MYDARKBLACK;
	else if (colorStr == "MYDARKGRAY") return MYDARKGRAY;
	else if (colorStr == "WHITE") return WHITE;
	else if (colorStr == "RED") return RED;
	else if (colorStr == "BLUE") return BLUE;
	else if (colorStr == "GREEN") return GREEN;
	else if (colorStr == "MYTHISTLE") return MYTHISTLE;
}
////////////////////////////////////////////////////////////////////  covert color to  string
string GUI::ColorToString(color clr)    //convert string to color type
{
	if (isMatchedColors(clr,DEEPSKYBLUE)) return "DEEPSKYBLUE";
	else if (isMatchedColors(clr, TOMATO)) return "TOMATO";
	else if (isMatchedColors(clr, LIGHTGREEN)) return "LIGHTGREEN";
	else if (isMatchedColors(clr, ORANGE)) return "ORANGE";
	else if (isMatchedColors(clr,BLACK)) return "BLACK";
	else if (isMatchedColors(clr, MYDARKBLACK)) return "MYDARKBLACK";
	else if (isMatchedColors(clr, MYDARKGRAY)) return "MYDARKGRAY";
	else if (isMatchedColors(clr, WHITE)) return "WHITE";
	else if (isMatchedColors(clr, RED)) return "RED"; 
	else if (isMatchedColors(clr, BLUE)) return "BLUE";
	else if (isMatchedColors(clr, GREEN)) return "GREEN";
	else if (isMatchedColors(clr, MYTHISTLE)) return "MYTHISTLE";
}

bool GUI::isMatchedColors(color c1, color c2)      //check if two color objects are matched
{
	if (c1.ucBlue == c2.ucBlue && c1.ucRed == c2.ucRed && c1.ucGreen == c2.ucGreen )
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

	pWind->DrawEllipse(center.x - length, center.y - height, center.x + length, center.y + height, style);
}

void GUI::DrawHex(int Xpoints[], int Ypoints[], GfxInfo HexGfxInfo, bool selected) const
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
