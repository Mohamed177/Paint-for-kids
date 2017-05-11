#pragma once
#include "Action.h"
class Scramble:public Action
{
	int True_counts, Fasle_counts;

public:
	Scramble(ApplicationManager *pApp);
	virtual bool ReadActionParameters();
	virtual void Execute();
};