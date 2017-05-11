#pragma once
#include "Action.h"
class Scramble:public Action
{
public:
	Scramble(ApplicationManager *pApp);
	virtual bool ReadActionParameters();
	virtual void Execute();
};