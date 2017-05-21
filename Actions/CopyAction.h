#pragma once
#include "Action.h"
class CopyAction :
	public Action
{
public:
	CopyAction(ApplicationManager * pApp);
	~CopyAction();
	bool ReadActionParameters();
	bool Execute();

	// Inherited via Action
	virtual void Undo() override;

	// Inherited via Action
	virtual void Redo() override;
};

