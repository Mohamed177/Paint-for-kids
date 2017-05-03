#pragma once
#include "Action.h"
class CutAction :
	public Action
{
public:
	CutAction(ApplicationManager * pApp);
	~CutAction();
	bool ReadActionParameters();
	void Execute();
};

