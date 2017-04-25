#pragma once
#include "Action.h"

class AddCircAction :public Action
{
public:
	AddCircAction(ApplicationManager *pApp);

	//Reads rectangle parameters
	virtual bool ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
	

private:
	Point Center, P2;
	GfxInfo RectGfxInfo;

};
