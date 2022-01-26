#include "ApplicationManager.h"
#include <fstream>
#include "Actions/ActionAddSquare.h"
#include "Actions/ActionAddEllipse.h"
#include "Actions/ActionAddHexagon.h"
#include "Actions/ActionSave.h"
#include "Actions/ActionLoad.h"
#include "Actions/ActionChangeLocation.h"
#include "Actions/ActionExit.h"
#include "Actions/ActionSelect.h"
#include "Actions/ActionMultiSelect.h"
#include "Actions/ActionChangeColor.h"
#include "Actions/ActionPickImage.h"
#include "Actions/ActionPickColor.h"
#include "Actions/ActionPickImage_Color.h"
#include "Actions/ActionSwitchPlay.h"
#include "Actions/ActionSwitchDraw.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	//delete all old figures
	ApplicationManager::ResetFigList();


	multiSelect = 0;
}

//delete all old figures
void ApplicationManager::ResetFigList()
{
	FigCount = 0;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{
		//1- Read user action
		ActType = pGUI->MapInputToActionType(x,y);

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;

		case DRAW_ELPS:
			newAct = new ActionAddEllipse(this);
			break;

		case DRAW_HEX:
			newAct = new ActionAddHexagon(this);
			break;

		case MUL_SELECT:
			newAct = new ActionMultiSelect(this,multiSelect);
			break;

		case SEND_BACK:
			//send to back
			newAct = new ActionChangeLocation(this,false);
			break;

		case BRNG_FRNT:
			//bring to front
			newAct = new ActionChangeLocation(this, true);
			break;

		case COLOR_RED:
			newAct = new ActionChangeColor(this, RED, DORF);
			break;

		case COLOR_BLUE:
			//create AddLineAction here
			newAct = new ActionChangeColor(this, BLUE, DORF);
			break;

		case COLOR_GREEN:
			//create AddLineAction here
			newAct = new ActionChangeColor(this, GREEN, DORF);
			break;

		case CHNG_DRAW_CLR:
			DORF = 1;
			break;

		case CHNG_FILL_CLR:
			DORF = 2;
			break;

		case CHNG_BK_CLR:
			DORF = 3;
			break;

		case SAVE:
			newAct = new ActionSave(this);
			break;

		case LOAD:
			newAct = new ActionLoad(this);
			break;

		case TO_PICK_IMAGE:
			newAct = new ActionPickImage(this);
			break;

		case TO_PICK_COLOR:
			newAct = new ActionPickColor(this);
			break;

		case TO_PICK_IMAGE_COLOR:
			newAct = new ActionPickImage_Color(this);
			break;

		case TO_PLAY:
			newAct = new ActionSwitchPlay(this);
			break;

		case TO_DRAW:
			newAct = new ActionSwitchDraw(this);
			break;

		case EXIT:
			newAct = new ActionExit(this);
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;

			// Khaled
		case  DRAWING_AREA:
			Point P;
			P.x = x; P.y = y;
			//pGUI->GetPointClicked(P.x, P.y); // this is the reason of double click // first click for entering this case and seconed one to send it to Action object  
			newAct = new ActionSelect(this, P, multiSelect);
			break;
	}	
	return newAct;
}

//////////////////////////////////////////////////////////////////////

//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}

//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//
// multiSelect filed
//bool ApplicationManager::multiSelect = false;
//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}

//unSelect Figures
void ApplicationManager::UnSelectFigures()const {
	for (int i = 0; i < FigCount ; i++) {
		FigList[i]->SetSelected(false);
	}
}
///////////////////////////////////////////////////////
// khaled
// func to return Selected Figure
CFigure *ApplicationManager::GetFigure(int x, int y) const         //get one selected figure by clicked point indexes
{
	// if the point in figure will return Pointer on Figure
	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i]->InFig(x, y))
		{
			return FigList[i];
		}
	}
	// if point not in any figure will return NULL
	return NULL;
}


CFigure *ApplicationManager::GetSelectedFigureByFlag(int& selectedIndex)     //get one selected figure by checking isSelected prop
{
	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i]->IsSelected())
		{
			selectedIndex = i;
			return FigList[i];
		}
	}
	// if no figure is selected return null
	return NULL;
}

void ApplicationManager::InsertFigure(bool isFront)          //insert figure in front or back of all figuers
{
	int selectedIndex;
	CFigure* temp = GetSelectedFigureByFlag(selectedIndex);
	if (temp == NULL)
	{

	}
	else
	{
		if (isFront)
		{
			for (int i =selectedIndex; i < FigCount; i++) {
				FigList[i] = FigList[i + 1];
			}
			FigList[FigCount - 1] = temp;
		}
		else
		{
			for (int i = selectedIndex; i >=0 ; i--) {
				FigList[i] = FigList[i - 1];
			}
			FigList[0] = temp;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////asmaa
void ApplicationManager::SaveAll(ofstream& File) const
{
	File << FigCount << endl;
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(File, GetGUI());
	}
}


////////////////////////////////////////////////////////////////////////////////////
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pGUI->ClearDrawArea(); // BY 'Mahmoud' If It Cause Problem
	for(int i=0; i<FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}

////////////////////////////////////////////////////////////////////////////////////

//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }

////////////////////////////////////////////////////////////////////////////////////

//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}
