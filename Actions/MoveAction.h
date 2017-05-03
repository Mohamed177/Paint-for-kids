#pragma once
#include "Action.h"
class MoveAction :
	public Action
{
	Point v;
public:
	MoveAction(ApplicationManager * pApp);
	~MoveAction();
	bool ReadActionParameters();
	void Execute();
};

