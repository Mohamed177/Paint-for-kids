#pragma once
#include"Action.h"

class ExitAction:public Action
{
public:
	ExitAction(ApplicationManager *pApp);

	virtual bool ReadActionParameters();

	virtual bool Execute();
	~ExitAction();

	// Inherited via Action
	virtual void Undo() override;

	// Inherited via Action
	virtual void Redo() override;
};

