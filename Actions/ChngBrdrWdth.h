#pragma once
#include"Action.h"

class ChngBrdrWdth : public Action
{

public:
	ChngBrdrWdth(ApplicationManager *pApp);
	
	~ChngBrdrWdth();
	 
	bool ReadActionParameters();

	void Execute();

};

