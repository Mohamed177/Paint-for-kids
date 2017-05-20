#pragma once
#include "Action.h"

class ChngBackClr : public Action
{
	color crntbkgrnd;
public:

	ChngBackClr(ApplicationManager *pApp);

	virtual bool ReadActionParameters();

	virtual bool Execute();

	~ChngBackClr();

	// Inherited via Action
	virtual void Undo() override;
};

