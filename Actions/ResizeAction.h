#pragma once
#include "Action.h"

class ResizeAction : public Action
{
	float factor;
public:

	virtual bool ReadActionParameters();

	virtual void Execute();

	ResizeAction(ApplicationManager *pApp);
	~ResizeAction();
};

