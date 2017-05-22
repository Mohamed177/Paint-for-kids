#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include"Action.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Action.h"
class SendFront :
	public Action
{
public:
	SendFront(ApplicationManager *);
	~SendFront();
	bool ReadActionParameters();
	bool Execute();
	virtual void Undo() override;

	// Inherited via Action
	virtual void Redo() override;
};

