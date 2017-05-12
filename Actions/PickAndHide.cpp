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

		if (ClickedItemOrder > 4) goto f; // To Take Another Point

		if (ClickedItemOrder == 4)    // Back Button Pressed
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
	if (b)   // "Back Button pressed"
	{
		pManager->ExecuteAction(TO_PLAY);
		return; 
	}                 
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

void PickAndHide::PH_DelFig(int index)
{
	delete figlist[index];
	figlist[index] = NULL;
	for (int j = index; j < figcount - 1; j++) // Move the empty hole to the end of the array
	{
		swap(figlist[j], figlist[j + 1]);
	}
	figcount--;


}


void PickAndHide::update()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearDrawArea();
	for (int i = 0; i < figcount; i++)
	{
		figlist[i]->Draw(pOut);
	}
}


void PickAndHide:: PH_TypeMode()
{
	char s = 'a';    // to get the type
	pManager->PickHideCopy(figlist, figcount);   // creating a new fig. to not affect the main one
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//pOut->CreateToolbar
	pOut->PrintMessage("Searching For Figures Via  ->> Type <<-  , Please Choose a Figure To Start");
	Point D;
	f:
	pIn->GetPointClicked(D.x, D.y);	//Get the coordinates of the user click

	 if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) // check that he pressed in the Drawing area
	{
		for (int i = 0; i < figcount; i++)
		{
			if(figlist[i]->Is_Selected(D))
			{
				s = figlist[i]->GetType(); // know which figure is it , line OR rect OR ...
				break;
			}
		}
		switch (s)
		{
		case 'L': pOut->PrintMessage("LINE !! Pick All Lines To Get A Perfect Score..");
			break;
		case 'R':  pOut->PrintMessage("RECTANGLE !! Pick All Rectangles To Get A Perfect Score..");
			break;
		case 'C': pOut->PrintMessage("CIRCLE !! Pick All Circles To Get A Perfect Score..");
			break;
		case 'T': pOut->PrintMessage("TRIANGLE !! Pick All Triangles To Get A Perfect Score..");
			break;

		default:
			goto f;
		}
	}
	else { goto f; } // Didn't press in Draw area

	

	int Fcount = 0; // When he clicks at a line , this will be the number of all lines , and so on
	                // for loop to get that number
	for (int  i = 0; i < figcount; i++)
	{
		if (figlist[i]->GetType()==s)
		{
			Fcount++;
		}
	}

	int Correct = 0;  // number of correct clicks
	int Wrong = 0;   // number of wrong clicks
	int c = Fcount; 
	while (Fcount != 0) 
	{
	
		
		Point D;
		pIn->GetPointClicked(D.x, D.y);
		if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) // check that he's INSIDE DRAW AREA
		{
			for (int i = figcount-1; i >=0; i--) // start mn el2a5er , 3l4an lw 2 fig drawen on each other
			{
				if (figlist[i]->Is_Selected(D) && s == figlist[i]->GetType())
				{
					Fcount--;
					Correct++;
					PH_DelFig(i);
					update(); // Re-Draw after i delete a fig.
					break;
				}
				else if (figlist[i]->Is_Selected(D)) 
				{
					Wrong++;
				}
			}
		}
		pOut->PrintMessage("RightClicks = " + to_string(Correct) + " , WrongClicks = " + to_string(Wrong));
	
	}

	if (Wrong>c) // 3l4an el negative (-4/0) :D
	{
		Wrong = c;
	}
	if ( Correct >= Wrong ) pOut->PrintMessage("Congratulations , Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :) ");
	else pOut->PrintMessage("Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :) ");
	if ( Wrong == 0 ) pOut->PrintMessage("PERFECT SCORE !! Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :) ");
	Sleep(4000);
}


void PickAndHide::PH_FillColorMode()
{
	int filled = 0; // to check if i pressed on a filled fig. , CUZ the base FILLCOLOR will mess with the code
	int selected = 0; // check if i pressed a filled fig or not 
	int s = 700;    // to get the Color
	pManager->PickHideCopy(figlist, figcount);   // creating a new fig. to not affect the main one
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//pOut->CreateToolbar
	pOut->PrintMessage("Searching For Figures Via  ->> Fill Color <<-  , Please Choose a Figure To Start");
	Point D;
f:
	pIn->GetPointClicked(D.x, D.y);	//Get the coordinates of the user click
	

	if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) // check that he pressed in the Drawing area
	{

		for (int i = 0; i < figcount; i++)
		{
			if (figlist[i]->Is_Selected(D) && (figlist[i]->ISFILLED()))
			{
				selected = 1;  // i pressed on a fig
				filled = 1;  // check if i pressed on a filled fig
				s = figlist[i]->GetFillInt(); // know which figure is it , line OR rect OR ...
				switch (s)
				{
				case 0:       pOut->PrintMessage("FILLED !! Pick All BLACK-FILLED Figures To Get A Perfect Score..");
					break;
				case 1:        pOut->PrintMessage("FILLED !! Pick All BLUE-FILLED Figures To Get A Perfect Score..");
					break;
				case 2:         pOut->PrintMessage("FILLED !! Pick All RED-FILLED Figures To Get A Perfect Score..");
					break;
				case 3:       pOut->PrintMessage("FILLED !! Pick All GREEN-FILLED Figures To Get A Perfect Score..");
					break;
				case 4:       pOut->PrintMessage("FILLED !! Pick All BROWN-FILLED Figures To Get A Perfect Score..");
					break;
				case 5:  pOut->PrintMessage("FILLED !! Pick All BLUEVIOLET-FILLED Figures To Get A Perfect Score..");
					break;
				case 6:        pOut->PrintMessage("FILLED !! Pick All CYAN-FILLED Figures To Get A Perfect Score..");
					break;
				case 7:   pOut->PrintMessage("FILLED !! Pick All DARKGREEN-FILLED Figures To Get A Perfect Score..");
					break;
				case 8:      pOut->PrintMessage("FILLED !! Pick All VIOLET-FILLED Figures To Get A Perfect Score..");
					break;
				case 9:        pOut->PrintMessage("FILLED !! Pick All GRAY-FILLED Figures To Get A Perfect Score..");
					break;
				case 10:      pOut->PrintMessage("FILLED !! Pick All ORANGE-FILLED Figures To Get A Perfect Score..");
					break;
				case 11:        pOut->PrintMessage("FILLED !! Pick All PINK-FILLED Figures To Get A Perfect Score..");
					break;
				case 12:    pOut->PrintMessage("FILLED !! Pick All SEAGREEN-FILLED Figures To Get A Perfect Score..");
					break;
				case 13:      pOut->PrintMessage("FILLED !! Pick All YELLOW-FILLED Figures To Get A Perfect Score..");
					break;
				case 14:      pOut->PrintMessage("FILLED !! Pick All LIGHTSKYBLUE-FILLED Figures To Get A Perfect Score..");
					break;

				default:
					goto f;
					break;
				}
			}

			else if (figlist[i]->Is_Selected(D) && !(figlist[i]->ISFILLED()))
			{
				selected = 1;
				s = figlist[i]->GetFillInt(); // know which figure is it , line OR rect OR ...
				pOut->PrintMessage("NON-FILLED !! Pick All NON-FILLED Figures To Get A Perfect Score..");
				break;
			}
			
		}

		if (selected == 0) goto f;
	}  
	          // Didn't press in Draw area
	else
	{
		goto f;
	} 

		int Fcount = 0; // When he clicks at a line , this will be the number of all lines , and so on
			         // for loop to get that number

		if (filled)
		{
			for (int i = 0; i < figcount; i++)
			{
				if (figlist[i]->GetFillInt() == s && figlist[i]->ISFILLED() )
				{
					Fcount++;
				}
			}
		}

		else
		{
			for (int i = 0; i < figcount; i++)
			{
				if (figlist[i]->GetFillInt() && !(figlist[i]->ISFILLED()))
				{
					Fcount++;
				}
			}
		}

		int Correct = 0;  // number of correct clicks
		int Wrong = 0;   // number of wrong clicks
		int c = Fcount;
		while (Fcount != 0)  
		{	
			Point D;
			pIn->GetPointClicked(D.x, D.y);
			if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) // check that he's INSIDE DRAW AREA
			{
				if (filled)
				{
					for (int i = figcount - 1; i >= 0; i--) // start mn el2a5er , 3l4an lw 2 fig drawen on each other
					{
						if (figlist[i]->Is_Selected(D) && s == figlist[i]->GetFillInt() && filled == 1)
						{
							Fcount--;
							Correct++;
							PH_DelFig(i);
							update(); // Re-Draw after i delete a fig.
							break;
						}
						else if (figlist[i]->Is_Selected(D))
						{
							Wrong++;
						}
					}
				}
				else
				{
					for (int i = figcount - 1; i >= 0; i--) // start mn el2a5er , 3l4an lw 2 fig drawen on each other
					{
						if (figlist[i]->Is_Selected(D) && s == figlist[i]->GetFillInt() && filled == 0 )
						{
							Fcount--;
							Correct++;
							PH_DelFig(i);
							update(); // Re-Draw after i delete a fig.
							break;
						}
						else if (figlist[i]->Is_Selected(D))
						{
							Wrong++;
						}
					}
				}
			}
			pOut->PrintMessage("RightClicks = " + to_string(Correct) + " , WrongClicks = " + to_string(Wrong) + " , Remaining Figures = " + to_string(c-Correct));
			// while loop so no need to goto
		}

		if (Wrong>c) // 3l4an el negative (-4/0) :D
		{
			Wrong = c;
		}
		if (Correct >= Wrong) pOut->PrintMessage("Congratulations , Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :) ");
		else pOut->PrintMessage("Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :) ");
		if (Wrong == 0) pOut->PrintMessage("PERFECT SCORE !! Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :) ");
		Sleep(1500);
	
}


void PickAndHide:: PH_TypeAndFillMode()
{
	pManager->PickHideCopy(figlist, figcount);
}

void PickAndHide:: PH_AreaMode()
{
	pManager->PickHideCopy(figlist, figcount);
}
