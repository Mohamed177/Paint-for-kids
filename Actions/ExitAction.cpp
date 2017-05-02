#include "ExitAction.h"
#include "SaveAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
ExitAction::ExitAction(ApplicationManager *pApp):Action(pApp)
{}

bool ExitAction::ReadActionParameters()
{
	if (SaveAction::No_of_Saves == 0)
		return false;
	return true;
}

void ExitAction::Execute()
{
	bool t = ReadActionParameters();
	if (!t)
	{
		SaveAction *pSaveAct = new SaveAction(pManager);
		delete pSaveAct;
		return;
	}

}

ExitAction::~ExitAction()
{}
