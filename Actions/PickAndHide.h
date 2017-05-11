#pragma once

#include "Action.h"

class PickAndHide : public Action
{
	int z=0; // 3l4an n3rf e5trna anhy mode f (pick and hide)
public:

	PickAndHide(ApplicationManager* pApp);

	~PickAndHide();

	bool ReadActionParameters();

	void Execute();
	
	void PH_TypeMode();

	void PH_FillColorMode();

	void PH_TypeAndFillMode();

	void PH_AreaMode();

};

