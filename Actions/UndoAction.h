#pragma once
#include "Action.h"

class UndoAction:public Action
{
public:
	UndoAction(ApplicationManager* pApp);
	~UndoAction();
	
private:


	// Inherited via Action
	virtual bool ReadActionParameters();

	virtual bool Execute();

	virtual void Undo();

	// Inherited via Action
	virtual void Redo() override;
};
