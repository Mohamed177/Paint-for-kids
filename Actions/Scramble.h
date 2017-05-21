#pragma once
#include "Action.h"
class Scramble:public Action
{
	int True_counts, False_counts;
	Point p;
public:
	Scramble(ApplicationManager *pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute();

	// Inherited via Action
	virtual void Undo() override;

	// Inherited via Action
	virtual void Redo() override;
};