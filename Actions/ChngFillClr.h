#pragma once
#include"Action.h"

class ChangeFillColor : public Action
{
public:
	ChangeFillColor(ApplicationManager *pApp);


	~ChangeFillColor();

	bool ReadActionParameters();

	void Execute();

};


