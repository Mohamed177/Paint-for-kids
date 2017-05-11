#include "PickAndHide.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


PickAndHide::PickAndHide(ApplicationManager* pApp) : Action (pApp)
{
	for (int i = 0; i < 200; i++)
	{
		figlist[i] = NULL;
	}
}


PickAndHide::~PickAndHide()
{
}

bool PickAndHide::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Welcome To Pick AND Hide Game :)  ");
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
			z = ClickedItemOrder;
			return true;
		}
		z = ClickedItemOrder;

	}
	else goto f;
	return false;
}

void PickAndHide::Execute()
{
f:
	Input* pIn = pManager->GetInput();
	bool b = ReadActionParameters();
	if (b) {
		pManager->ExecuteAction(TO_PLAY);
		return; } // "Back Button pressed"
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
	default:
		goto f;
		break;
	}
	pManager->UpdateInterface(TO_PLAY);
	goto f;
}

void PickAndHide:: PH_TypeMode()
{
	char s = 'a'; // to get the type
	pManager->PickHideCopy(figlist, figcount);
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//pOut->CreateToolbar
	pOut->PrintMessage("Playing Via Figures Type , Please Choose a Figure To Start");
	Point D;
	f:
	pIn->GetPointClicked(D.x, D.y);	//Get the coordinates of the user click
	if (D.y <= UI.ToolBarHeight && D.y>0)
	{
		int ClickedItemOrder = (D.x / UI.MenuItemWidth);
		if (ClickedItemOrder == 0)
		{
			return;
		}

	}
	else if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) 
	{
		for (int i = 0; i < figcount; i++)
		{
			if(figlist[i]->Is_Selected(D))
			{
				s = figlist[i]->GetType();
				break;
			}
		}
		switch (s)
		{
		case 'L': pOut->PrintMessage("LINE !! Select All Lines And Get A Perfect Score..");
			break;
		case 'R':  pOut->PrintMessage("RECTANGLE !! Select All Rectangles And Get A Perfect Score..");
			break;
		case 'C': pOut->PrintMessage("CIRCLE !! Select All Circles And Get A Perfect Score..");
			break;
		case 'T': pOut->PrintMessage("TRIANGLE !! Select All Triangles And Get A Perfect Score..");
			break;

		default:
			goto f;
		}
	}
	else { goto f; }
	Sleep(1500);
	int Fcount = 0;
	for (int  i = 0; i < figcount; i++)
	{
		if (figlist[i]->GetType()==s)
		{
			Fcount++;
		}
	}
	int good = 0;
	int bad = 0;
	int c = Fcount;
	while (Fcount != 0) 
	{
		pOut->PrintMessage("RightClicks = " + to_string(good) + " , WrongClicks = " + to_string(bad));
		Point D;
		pIn->GetPointClicked(D.x, D.y);
		if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight))
		{
			for (int i = figcount-1; i >=0; i--)
			{
				if (figlist[i]->Is_Selected(D) && s == figlist[i]->GetType())
				{
					Fcount--;
					good++;
					PH_DelFig(i);

					update();
					break;
				}
				else if (figlist[i]->Is_Selected(D)) 
				{
					bad++;
				}
			}
		}
	
	}
	if (bad>c)
	{
		bad = c;
	}
	pOut->PrintMessage("Congratulations , your score is " + to_string(c - bad) + "/" + to_string(c) + " , thanks for playing :) .");
	Sleep(2000);
}

void PickAndHide:: PH_FillColorMode()
{
	pManager->PickHideCopy(figlist, figcount);
}

void PickAndHide:: PH_TypeAndFillMode()
{
	pManager->PickHideCopy(figlist, figcount);
}

void PickAndHide:: PH_AreaMode()
{
	pManager->PickHideCopy(figlist, figcount);
}
void PickAndHide::PH_DelFig( int index) 
{
			delete figlist[index];
			figlist[index] = NULL;
			for (int j = index; j < figcount - 1; j++)
			{
				swap(figlist[j], figlist[j + 1]);
			}
			figcount--;
		
	
}
void PickAndHide::update() 
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearDrawArea();
	for (int  i = 0; i < figcount; i++)
	{
		figlist[i]->Draw(pOut);
	}
}