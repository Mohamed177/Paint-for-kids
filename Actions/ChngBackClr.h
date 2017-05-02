#pragma once
#include "Action.h"
class ChngBackClr:public Action
{
public:
	ChngBackClr(ApplicationManager *pApp);
	virtual bool ReadActionParameters();

	virtual void Execute();
	~ChngBackClr();
};

