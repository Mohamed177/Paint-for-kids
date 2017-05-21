#pragma once
#include "Action.h"
class AddTriAction :
	public Action
{
	Point p1;
	Point p2;
	Point p3;
	GfxInfo triGfxInfo;
public:
	AddTriAction(ApplicationManager *pApp);
	//Reads trangle parameters
	virtual bool ReadActionParameters();

	//Add triangle to the ApplicationManager
	virtual bool Execute();

	~AddTriAction();

	// Inherited via Action
	virtual void Undo() override;

	// Inherited via Action
	virtual void Redo() override;
};

