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
	pOut->PrintMessage("click at any  point to move the figures ");
	pIn->GetPointClicked(v.x, v.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

	return true;
}

void MoveAction::Execute()
{
	 bool t = ReadActionParameters();
	 t = pManager->move(v);
	 Output* pOut = pManager->GetOutput();
	 if (!t)
	 {
		 pOut->PrintMessage("you can't move figures here try somewhere else :)");
	 }
	 pOut->ClearStatusBar();
	 pManager->Saved = false;
	 pManager->first_zoom = true;

}


MoveAction::~MoveAction()
{
}
