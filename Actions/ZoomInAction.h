#pragma once
#include "Action.h"
#include <stack>
class ZoomIn : public Action
{
	image S_Shot;
public:

	static int ZoomIns;

	ZoomIn(ApplicationManager *pApp);

	virtual bool ReadActionParameters();

	virtual void Execute();

	~ZoomIn();
};

