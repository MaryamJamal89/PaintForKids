#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"

class Action;	//Forward Declaration

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int x, y;			//click points on Screen
	int FigCount;		//Actual number of figures
	int DORF =0;		//Draw or fill or backgoround 
	 
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	//Pointers to Input and Output classes
	GUI* pGUI;

public:	
	int multiSelect;//enabling multiSelect
	ApplicationManager(); 
	~ApplicationManager();

	void ResetFigList(); //deletes all old figures
	
	void Run();		//to run the application
	
	// -- Action-Related Functions
	Action* CreateAction(ActionType);
	void ExecuteAction(Action*&) ; //Execute an action
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure

	CFigure* GetSelectedFigureByFlag(int& selectedIndex, int& selectedNum);
	void InsertFigure(bool isFront);  //change location of selected figure to back or front
		
	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window	

	// Saving function
	void SaveAll(ofstream& File)const;       //Save All Figures To The File :Asmaa

	void UnSelectFigures() const;
};

#endif