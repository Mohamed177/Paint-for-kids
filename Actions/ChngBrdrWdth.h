#pragma once
#include"Action.h"

class ChngBrdrWdth : public Action
{
	int crntbrdr;
public:
	ChngBrdrWdth(ApplicationManager *pApp);
	
	~ChngBrdrWdth();
	 
	bool ReadActionParameters();

	bool Execute();


	// Inherited via Action
	virtual void Undo() override;

};

