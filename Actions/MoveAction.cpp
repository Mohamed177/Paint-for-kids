#include "MoveAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


MoveAction::MoveAction(ApplicationManager * pApp) :Action(pApp)
{
	v.x = 0;
	v.y = 0;
}
bool MoveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("click theat any  point to move the figures ");
	pIn->GetPointClicked(v.x, v.y);
	return true;
}

void MoveAction::Execute()
{
	bool t = ReadActionParameters();
	 t = pManager->move(v);
	 if (!t)
	 {
		 Output* pOut = pManager->GetOutput();
		 pOut->PrintMessage("you can't move figures here try somewhere else :)");
	 }
}


MoveAction::~MoveAction()
{
}
