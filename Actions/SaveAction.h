#pragma once
#include "Action.h"
#include <fstream>
class SaveAction : public Action
{
	ofstream OutFile;
	string FileName;
public:
	bool ReadActionParameters();
	bool Execute();
	SaveAction(ApplicationManager* pApp);
	~SaveAction();

	// Inherited via Action
	virtual void Undo() override;
};

