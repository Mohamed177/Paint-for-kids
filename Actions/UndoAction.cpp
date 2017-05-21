#include "UndoAction.h"
#include "..\ApplicationManager.h"

UndoAction::UndoAction(ApplicationManager* pApp):Action(pApp)
{
}

UndoAction::~UndoAction()
{
}

bool UndoAction::ReadActionParameters()
{
	return false;
}

bool UndoAction::Execute()
{
	if (!pManager->UndoList.empty())
	{
		Action* ptr = pManager->UndoList.top();
		ptr->Undo();
		pManager->UndoList.pop();
		pManager->RedoList.push(ptr);
	}
	return false;
	pManager->Saved = false;
	pManager->GetOutput()->ClearStatusBar();
}

void UndoAction::Undo()
{
}

void UndoAction::Redo()
{
}
