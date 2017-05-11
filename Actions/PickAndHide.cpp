#include "PickAndHide.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


PickAndHide::PickAndHide(ApplicationManager* pApp) : Action (pApp)
{
}


PickAndHide::~PickAndHide()
{
}

bool PickAndHide::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Point D;
	pOut->CreatePickHideToolbar();
f:
	int x, y;
	pIn->GetPointClicked(x, y);	//Get the coordinates of the user click

		//[1] If user clicks on the Toolbar
	if (y >= 0 && y < UI.ToolBarHeight)
	{
		//Check whick Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = (x / UI.MenuItemWidth);
		//Divide x coord of the point clicked by the menu item width (int division)
		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

		if (ClickedItemOrder > 4) goto f;
		if (ClickedItemOrder == 4)
		{
			pOut->ClearToolBar();
			pOut->CreatePickHideToolbar();
			return true;
		}
		z = ClickedItemOrder;

	}
	else goto f;
	return false;
}

void PickAndHide::Execute()
{
	bool b = ReadActionParameters();
	if (b) { return; } // "Back Button pressed"
	switch (z)
	{
	case  0: PH_TypeMode();
		break;
	case 1: PH_FillColorMode();
		break;
	case 2: PH_TypeAndFillMode();
		break;
	case 3: PH_AreaMode();
		break;


	default: return;
		break;
	}
}

void PickAndHide:: PH_TypeMode()
{
	Output* pOut = pManager->GetOutput();
}

void PickAndHide:: PH_FillColorMode()
{

}

void PickAndHide:: PH_TypeAndFillMode()
{

}

void PickAndHide:: PH_AreaMode()
{

}