#pragma once
#include "Action.h"
#include <fstream>
class SaveAction : public Action
{
	ofstream OutFile;
public:
	static int No_of_Saves;
	static string FileName;
	bool ReadActionParameters();
	void Execute();
	SaveAction(ApplicationManager* pApp);
	~SaveAction();
};

