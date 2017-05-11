#include "ChngBackClr.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


ChngBackClr::ChngBackClr(ApplicationManager *pApp):Action(pApp)
{
}

bool ChngBackClr::ReadActionParameters()
{

	return true;
}

void ChngBackClr::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateColorToolBar();
	pOut->PrintMessage("Choose The New Back Ground Color. ");
	pOut->setBackColor(pIn->ChangeBackColor());
	pOut->ClearToolBar();
	pOut->CreateDrawToolBar();
	pManager->Saved = false;

}

ChngBackClr::~ChngBackClr()
{
}
