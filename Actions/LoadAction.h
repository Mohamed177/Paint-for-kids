#pragma once
#include "Action.h"
#include <fstream>
class LoadAction :
	public Action
{
	ifstream LoadFile;
	string FileName;
public:
	bool ReadActionParameters();
	bool Execute();
	LoadAction(ApplicationManager* pApp);
	~LoadAction();

	// Inherited via Action
	virtual void Undo() override;
};

