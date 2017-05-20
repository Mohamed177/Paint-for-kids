#pragma once

#include "Action.h"
#include"../Figures/CFigure.h"

class PickAndHide : public Action
{
	int z=0; // 3l4an n3rf e5trna anhy mode f (pick and hide)

	CFigure* figlist[200];

	int figcount = 0;

	int score = 0;
public:

	PickAndHide(ApplicationManager* pApp);

	~PickAndHide();

	bool ReadActionParameters();

	bool Execute();
	
	void PH_TypeMode();

	void PH_FillColorMode();

	void PH_TypeAndFillMode();

	void PH_AreaMode();

	void PH_DelFig(int index);

	void update();


	// Inherited via Action
	virtual void Undo() override;

};

