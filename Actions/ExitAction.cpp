#include "ExitAction.h"
#include "SaveAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
ExitAction::ExitAction(ApplicationManager *pApp):Action(pApp)
{}

bool ExitAction::ReadActionParameters()
{
	PlaySound(NULL, NULL, 0);
	PlaySound("whyexit.WAV", NULL, SND_LOOP | SND_ASYNC);
	int x, y;
	if (pManager->Saved)
		return false;
	Output* pOut = pManager->GetOutput();
	if ( UI.InterfaceMode == MODE_DRAW )
		pOut->DrawIMAGE("exitCE", 1220, 0, 61, 50);
	else if (UI.InterfaceMode == MODE_ZOOM)
		pOut->DrawIMAGE("exitCE", 1217, 0, 58, 50);
	else pOut->DrawIMAGE("exitCE", 183, 0, 61, 50);

	Input *pIn = pManager->GetInput();
	pOut->DrawIMAGE("exitwind", 380, 231, 833-380, 429-231);
	f:
	pIn->GetPointClicked(x, y);	//Get the coordinates of the user click
	if (435 <= x && x <= 569 && y >= 355 && y <= 387) 
		return false;
	else if ( (664 <= x && x <= 797) && (y >= 366 && y <= 395))
		return true;
	else
		goto f;
	
}

void ExitAction::Execute()
{
	bool t = ReadActionParameters();
	if (t)
		pManager->ExecuteAction(SAVE);
	
}

ExitAction::~ExitAction()
{}
