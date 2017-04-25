#pragma once
#include "Action.h"
#include <fstream>
class SaveAction : public Action
{
	ofstream OutFile;
	string FileName;
public:
	bool ReadActionParameters();
	void Execute();
	SaveAction(ApplicationManager* pApp);
	~SaveAction();
};

