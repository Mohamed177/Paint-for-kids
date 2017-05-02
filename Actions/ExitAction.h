#pragma once
#include"Action.h"

class ExitAction:public Action
{
public:
	ExitAction(ApplicationManager *pApp);

	virtual bool ReadActionParameters();

	virtual void Execute();
	~ExitAction();
};

