#include "RedoAction.h"
#include "..\ApplicationManager.h"

RedoAction::RedoAction(ApplicationManager *pApp):Action(pApp)
{
}

RedoAction::~RedoAction()
{
}

bool RedoAction::ReadActionParameters()
{
	return false;
}

bool RedoAction::Execute()
{
	if (!pManager->RedoList.empty())
	{
		Action* ptr = pManager->RedoList.top();
		ptr->Redo();
		pManager->RedoList.pop();
		pManager->UndoList.push(ptr);
	}
	return false;
	pManager->Saved = false;
	pManager->GetOutput()->ClearStatusBar();
}

void RedoAction::Undo()
{
}

void RedoAction::Redo()
{
}
