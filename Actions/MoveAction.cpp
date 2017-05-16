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
	pOut->DrawIMAGE("MoveCE", 610, 0, 61, 50);
	pOut->PrintMessage("click at any  point to move the figures ");
	pIn->GetPointClicked(v.x, v.y);
	
	
	return true;
}

void MoveAction::Execute()
{
	 bool t = ReadActionParameters();
	 t = pManager->move(v);
	 Output* pOut = pManager->GetOutput();
	 if (!t)
	 {
		 pOut->DrawIMAGE("Move", 610, 0, 61, 50);
		 pOut->PrintMessage("you can't move figures here try somewhere else :)");
	 }
	 pOut->ClearStatusBar();
	 pOut->DrawIMAGE("Move", 610, 0, 61, 50);
}


MoveAction::~MoveAction()
{
}
