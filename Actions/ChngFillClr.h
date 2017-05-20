#pragma once
#include"Action.h"

class ChangeFillColor : public Action
{
	color crntfllclr;
public:
	ChangeFillColor(ApplicationManager *pApp);


	~ChangeFillColor();

	bool ReadActionParameters();

	bool Execute();


	// Inherited via Action
	virtual void Undo() override;

};


