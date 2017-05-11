#pragma once
#include "Action.h"
#include "ZoomInAction.h"
class ZoomOutAction : public Action
{
public:
	static int ZoomOuts;

	ZoomOutAction(ApplicationManager *pApp);

	virtual bool ReadActionParameters();

	virtual void Execute();
	~ZoomOutAction();
};

