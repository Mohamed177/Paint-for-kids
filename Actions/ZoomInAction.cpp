#include "ZoomInAction.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"
#include "ZoomOutAction.h"
int ZoomIn::ZoomIns = -1;

ZoomIn::ZoomIn(ApplicationManager *pApp):Action(pApp)
{
	if (ZoomOutAction::ZoomOuts < 0)
		ZoomIns++;
}

bool ZoomIn::ReadActionParameters()
{
	return true;
}

//Execute the action
void ZoomIn::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	int DrawHeight = (UI.height - (UI.ToolBarHeight + UI.StatusBarHeight)) / 16;
	if (ZoomOutAction::ZoomOuts >= 0)
	{
		pOut->ClearDrawArea();
		pOut->DrawImage(pManager->zoomout[ZoomOutAction::ZoomOuts--], 0, UI.ToolBarHeight, UI.width, 16 * DrawHeight);
		return;
	}
	pOut->StoreImage(S_Shot, UI.width / 16, UI.ToolBarHeight + DrawHeight, UI.width * 14 / 16, 14 * DrawHeight);
	pOut->StoreImage(pManager->zoomin[ZoomIns], 0, UI.ToolBarHeight, UI.width, UI.height - (UI.ToolBarHeight + UI.StatusBarHeight));
	pOut->ClearDrawArea();
	pOut->DrawImage(S_Shot, 0, UI.ToolBarHeight, UI.width, UI.height - (UI.ToolBarHeight + UI.StatusBarHeight));
	pOut->ClearStatusBar();
}


ZoomIn::~ZoomIn()
{
}
