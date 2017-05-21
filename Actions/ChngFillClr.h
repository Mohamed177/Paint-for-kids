#pragma once
#include"Action.h"

class ChangeFillColor : public Action
{
	color crntfllclr, newclr;
public:
	ChangeFillColor(ApplicationManager *pApp);


	~ChangeFillColor();

	bool ReadActionParameters();

	bool Execute();


	// Inherited via Action
	virtual void Undo() override;


	// Inherited via Action
	virtual void Redo() override;

};


