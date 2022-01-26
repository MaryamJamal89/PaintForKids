#pragma once
//#ifndef ACTION_SELECT_H
//#define ACTION_SELECT_H
#include"..\ApplicationManager.h"
#include "Action.h"
class ActionSelect :
    public Action
{

private:
    Point P;
    bool multiSelect;
public:
    // make that constructor take x & y when creation
    ActionSelect(ApplicationManager* pApp, Point _P,bool _multiSelect);
    //  Select Fugure 
    virtual void Execute();
};

