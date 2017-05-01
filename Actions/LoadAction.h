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
	void Execute();
	LoadAction(ApplicationManager* pApp);
	~LoadAction();
};

