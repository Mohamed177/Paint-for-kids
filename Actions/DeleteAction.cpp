#include "DeleteAction.h"
#include "SelectAction.h"

DeleteAction::DeleteAction(ApplicationManager * p):Action(p)
{

}

bool DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Figures have been deleted");
	return 1;
}

bool DeleteAction::Execute()
{
	bool done = pManager->Delete_Figs();
	Output* pOut = pManager->GetOutput();
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() > 0)
		pOut->CreateZoomToolBar();
	else if (UI.InterfaceMode == MODE_ZOOM)
		pOut->CreateSelcted_ZoomToolBar();
	else
		pOut->CreateDrawToolBar();
	pManager->Saved = false;
	if (UI.InterfaceMode == MODE_DRAW)
		pManager->first_zoom = true;

	
	pManager->Saved = false;

	if (UI.InterfaceMode == MODE_ZOOM)
	{
		Output* pOut = pManager->GetOutput();
		pOut->Clickeffect("Delete", ZOOM_DEL * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	else 
	{
		Output* pOut = pManager->GetOutput();
		pOut->Clickeffect("Delete", ITM_DEL * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	
	}
	if (done)
		while (!pManager->RedoList.empty())
			pManager->RedoList.pop();
	return done;
}

DeleteAction::~DeleteAction()
{
	
}

void DeleteAction::Undo()
{
	pManager->Undo(DEL);
}

void DeleteAction::Redo()
{
	pManager->Redo(DEL);
}
