#pragma once
#include "Action.h"
class RedoAction : public Action
{
public:
	RedoAction(ApplicationManager *pApp);
	~RedoAction();

private:


	// Inherited via Action
	virtual bool ReadActionParameters() override;

	virtual bool Execute() override;

	virtual void Undo() override;


	// Inherited via Action
	virtual void Redo() override;

};
