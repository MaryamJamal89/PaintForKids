#pragma once
#include"..\ApplicationManager.h"
#include "Action.h"
#include <vector>

using namespace std;

class ActionSelect : public Action
{
	Point P;
	bool multiSelect;
	int playType;
	//vector <CFigure*> selectedFigures;
public:
	// make that constructor take x & y when creation
	ActionSelect(ApplicationManager* pApp, Point _P, bool _multiSelect, int _playType);
	//  Select Fugure 
	virtual void Execute();
};

