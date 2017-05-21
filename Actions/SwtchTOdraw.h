#pragma once
#include"Action.h"


class SwtchTOdraw : public Action
{

public:
	SwtchTOdraw(ApplicationManager *pApp);

	~SwtchTOdraw();

	bool ReadActionParameters();

	bool Execute();


	// Inherited via Action
	virtual void Undo() override;


	// Inherited via Action
	virtual void Redo() override;

};

