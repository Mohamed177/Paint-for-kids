#pragma once
#include "Action.h"
#include <stack>
class ZoomIn : public Action
{
public:


	ZoomIn(ApplicationManager *pApp);

	virtual bool ReadActionParameters();

	virtual bool Execute();

	~ZoomIn();

	// Inherited via Action
	virtual void Undo() override;
};

