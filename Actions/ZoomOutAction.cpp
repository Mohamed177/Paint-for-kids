#include "ZoomOutAction.h"
#include "../ApplicationManager.h"
#include "..\GUI\Output.h"
#include "../GUI/Input.h"

int ZoomOutAction::ZoomOuts = -1;

ZoomOutAction::ZoomOutAction(ApplicationManager *pApp):Action(pApp)
{
	if (ZoomIn::ZoomIns < 0)
		ZoomOuts++;
}


ZoomOutAction::~ZoomOutAction()
{
}
bool ZoomOutAction::ReadActionParameters()
{
	return true;
}

void ZoomOutAction::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	int DrawHeight = (UI.height - (UI.ToolBarHeight + UI.StatusBarHeight)) / 16;
	if (ZoomIn::ZoomIns >=0)
	{
		pOut->ClearDrawArea();
		pOut->DrawImage(pManager->zoomin[ZoomIn::ZoomIns--], 0, UI.ToolBarHeight, UI.width, 16*DrawHeight);
		return;
	}
	pOut->StoreImage(pManager->zoomout[ZoomOuts], 0, UI.ToolBarHeight, UI.width, UI.height - (UI.ToolBarHeight + UI.StatusBarHeight));
	pOut->StoreImage(S_Shot, 0, UI.ToolBarHeight + 5, UI.width - 15, UI.height - (UI.ToolBarHeight + UI.StatusBarHeight) - 5);
	pOut->ClearDrawArea();
	pOut->DrawImage(S_Shot, UI.width / 16, UI.ToolBarHeight + DrawHeight, UI.width * 14 / 16, 14 * DrawHeight);
	pOut->ClearStatusBar();
}