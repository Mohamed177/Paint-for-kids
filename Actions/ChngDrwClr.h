#pragma once
#include"Action.h"

class ChangeDrawColor : public Action
{
public:
	ChangeDrawColor(ApplicationManager *pApp);


	~ChangeDrawColor();

	bool ReadActionParameters();

	void Execute();

};


