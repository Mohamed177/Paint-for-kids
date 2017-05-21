#pragma once
#include "Action.h"

class ResizeAction : public Action
{
	float factor;
public:

	virtual bool ReadActionParameters();

	virtual bool Execute();

	ResizeAction(ApplicationManager *pApp);
	~ResizeAction();

	// Inherited via Action
	virtual void Undo() override;

	// Inherited via Action
	virtual void Redo() override;
};

