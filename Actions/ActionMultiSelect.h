#pragma once
#include "Action.h"

class ActionMultiSelect : public Action
{
private:
    int* multiSelect;
public:
    ActionMultiSelect(ApplicationManager* pApp, int& _multiSelect);
    virtual void Execute();
};
