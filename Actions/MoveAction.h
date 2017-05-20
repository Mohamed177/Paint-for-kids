#pragma once
#include "Action.h"
class MoveAction :
	public Action
{
	Point v, Center;
public:
	MoveAction(ApplicationManager * pApp);
	~MoveAction();
	bool ReadActionParameters();
	bool Execute();

	// Inherited via Action
	virtual void Undo() override;
};

