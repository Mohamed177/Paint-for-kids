#pragma once
#include "Action.h"
#include <stack>
class ZoomIn : public Action
{
public:


	ZoomIn(ApplicationManager *pApp);

	virtual bool ReadActionParameters();

	virtual void Execute();

	~ZoomIn();
};

