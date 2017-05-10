#include "ExitAction.h"
#include "SaveAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
ExitAction::ExitAction(ApplicationManager *pApp):Action(pApp)
{}

bool ExitAction::ReadActionParameters()
{
	if (pManager->Saved)
		return true;
	Output* pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	pOut->PrintMessage("Your graph is not saved, enter y to save and n to exit without saving.");
	string answer = pIn->GetSrting(pOut);
	if (answer == "y" || answer == "Y")
		return true;
	return false;
}

void ExitAction::Execute()
{
	bool t = ReadActionParameters();
	if (t)
		pManager->ExecuteAction(SAVE);
}

ExitAction::~ExitAction()
{}
