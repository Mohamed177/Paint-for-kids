#include "DeleteAction.h"

DeleteAction::DeleteAction(ApplicationManager * p):Action(p)
{
}

bool DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Figures have been deleted");
	return 1;
}

void DeleteAction::Execute()
{
	pManager->Delete_Figs();
	pManager->Saved = false;
}

