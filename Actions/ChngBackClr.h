#pragma once
#include "Action.h"

class ChngBackClr : public Action
{
	color crntbkgrnd, newclr;
public:

	ChngBackClr(ApplicationManager *pApp);

	virtual bool ReadActionParameters();

	virtual bool Execute();

	~ChngBackClr();

	// Inherited via Action
	virtual void Undo() override;

	// Inherited via Action
	virtual void Redo() override;
};

