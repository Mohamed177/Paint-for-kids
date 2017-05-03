#pragma once
#include "Action.h"
class CopyAction :
	public Action
{
public:
	CopyAction(ApplicationManager * pApp);
	~CopyAction();
	bool ReadActionParameters();
	void Execute();
};

