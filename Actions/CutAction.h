#pragma once
#include "Action.h"
class CutAction :
	public Action
{
public:
	CutAction(ApplicationManager * pApp);
	~CutAction();
	bool ReadActionParameters();
	bool Execute();

	// Inherited via Action
	virtual void Undo() override;
};

