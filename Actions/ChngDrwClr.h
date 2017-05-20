#pragma once
#include"Action.h"

class ChangeDrawColor : public Action
{
	color crntdrwclr;
public:
	ChangeDrawColor(ApplicationManager *pApp);


	~ChangeDrawColor();

	bool ReadActionParameters();

	bool Execute();


	// Inherited via Action
	virtual void Undo() override;

};


