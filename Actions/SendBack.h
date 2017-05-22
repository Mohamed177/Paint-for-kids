#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include"Action.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
class SendBack :
	public Action
{
public:
	SendBack(ApplicationManager *);
	~SendBack();
	bool ReadActionParameters();
	bool Execute();
	virtual void Undo() ;

	// Inherited via Action
	virtual void Redo() ;
};

