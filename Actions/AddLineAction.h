#pragma once
#include "Action.h"
class AddLineAction :
	public Action
{
private:
	Point p1, p2; //Line Points
	GfxInfo LineGfxInfo;
public:
	AddLineAction(ApplicationManager *pApp);

	//Reads Line parameters
	virtual bool ReadActionParameters();

	//Add Line to the ApplicationManager
	virtual void Execute();

	~AddLineAction();
};

