#pragma once
#include"Action.h"


class SwtchTOdraw : public Action
{

public:
	SwtchTOdraw(ApplicationManager *pApp);

	~SwtchTOdraw();

	bool ReadActionParameters();

	void Execute();

};

