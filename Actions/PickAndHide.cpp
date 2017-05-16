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
	PlaySound(NULL, NULL, 0);
	PlaySound("ph.WAV", NULL, SND_LOOP | SND_ASYNC);
}


PickAndHide::~PickAndHide()
{
}

bool PickAndHide::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Welcome To Pick AND Hide Game , Please Choose a Mode From The Toolbar :)  ");
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
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	bool b = ReadActionParameters();
	if (b)   // "Back Button pressed"
	{
		pOut->CreatePlayToolBar();
		return; 
	}                 
	switch (z)
	{
	case  0:  PH_TypeMode();
		break;
	case 1: PH_FillColorMode(); 
		break;
	case 2:  PH_TypeAndFillMode(); 
		break;
	case 3:  PH_AreaMode(); 
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
	Output* pOut = pManager->GetOutput();
	pOut->DrawIMAGE("PH_FigsCE", 0, 0, 61, 50);
	int mssg = 0; // to print the message , look @ the end of the func.
	char s = 'a';    // to get the type
	pManager->PickHideCopy(figlist, figcount);   // creating a new figlist. to not affect the main one
	Input* pIn = pManager->GetInput();

	//pOut->CreateToolbar
	pOut->PrintMessage("Searching For Figures Via  ->> Type <<-  , Please Choose a Figure To Start");
	Point D;
	f:
	pIn->GetPointClicked(D.x, D.y);	//Get the coordinates of the user click

	 if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) // check that he pressed in the Drawing area
	{
		for (int i = figcount-1; i >=0; i--)
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

					mciSendString(TEXT("play correct.wav"), NULL, 0, NULL);
					
					Fcount--;
					Correct++;
					PH_DelFig(i);
					update(); // Re-Draw after i delete a fig.
					break;
				}
				else if (figlist[i]->Is_Selected(D)) 
				{
					
					mciSendString(TEXT("play wrong.wav"), NULL, 0, NULL);

					Wrong++;
				}
			}
		}
		pOut->PrintMessage("RightClicks = " + to_string(Correct) + "                   WrongClicks = " + to_string(Wrong) + "                   Remaining Figures = " + to_string(c - Correct));
	
	}
	//pOut->DrawIMAGE("PH_Figs", 0, 0, 61, 50);
	if (Wrong>c) // 3l4an el negative (-4/0) :D
	{
		Wrong = c;
	}
	if (c - Wrong == 0)
	{
		mssg = 2;
		PlaySound(NULL, NULL, 0);
		PlaySound("boo.WAV", NULL, SND_ASYNC);
	}
	else if (Correct >= Wrong && Wrong != 0)
	{
		mssg = 1;
		PlaySound(NULL, NULL, 0);
		PlaySound("kids.WAV", NULL, SND_ASYNC);
	}
	else if (Wrong == 0)
	{
		mssg = 3;
		PlaySound(NULL, NULL, 0);
		PlaySound("kids.WAV", NULL, SND_ASYNC);
	}

	for (int i = 3; i > 0; i--)
	{

		switch (mssg)
		{
		case 1:     pOut->PrintMessage("Congratulations , Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
			break;
		case 2:     pOut->PrintMessage("Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
			break;
		case 3:     pOut->PrintMessage("PERFECT SCORE !! Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
			break;

		default:  pOut->PrintMessage("                                 Restarting in " + to_string(i) + " Seconds ...");
			break;
		}
		Sleep(1000);
	}

	PlaySound(NULL, NULL, 0);
	PlaySound("ph.WAV", NULL, SND_LOOP | SND_ASYNC);




}


void PickAndHide::PH_FillColorMode()
{
	Output* pOut = pManager->GetOutput();
	pOut->DrawIMAGE("PH_FillColorCE", 61, 0, 61, 50);
	int mssg = 0; // to print the message , look @ the end of the func.
	int filled = 0; // to check if i pressed on a filled fig. , CUZ the base FILLCOLOR will mess with the code
	int selected = 0; // check if i pressed a filled fig or not 
	int s = 700;    // to get the Color
	pManager->PickHideCopy(figlist, figcount);   // creating a new fig. to not affect the main one
	Input* pIn = pManager->GetInput();

	//pOut->CreateToolbar
	pOut->PrintMessage("Searching For Figures Via  ->> Fill Color <<-  , Please Choose a Figure To Start");
	Point D;
f:
	pIn->GetPointClicked(D.x, D.y);	//Get the coordinates of the user click
	

	if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) // check that he pressed in the Drawing area
	{

		for (int i = figcount - 1; i >= 0; i--)  // 3l4an e5tar elly foo2
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
				case 5:     pOut->PrintMessage("FILLED !! Pick All BLUEVIOLET-FILLED Figures To Get A Perfect Score..");
					break;
				case 6:        pOut->PrintMessage("FILLED !! Pick All CYAN-FILLED Figures To Get A Perfect Score..");
					break;
				case 7:      pOut->PrintMessage("FILLED !! Pick All DARKGREEN-FILLED Figures To Get A Perfect Score..");
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
				break; // after the switch
			}

			else if (figlist[i]->Is_Selected(D) && ! (figlist[i]->ISFILLED()) )
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
				if ( ( figlist[i]->GetFillInt() == s ) && figlist[i]->ISFILLED() )
				{
					Fcount++;
				}
			}
		}

		else
		{
			for (int i = 0; i < figcount; i++)
			{
				if ( ! (figlist[i]->ISFILLED()))
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
						if (figlist[i]->Is_Selected(D) && s == figlist[i]->GetFillInt() && figlist[i]->ISFILLED())
						{
							mciSendString(TEXT("play correct.wav"), NULL, 0, NULL);
							Fcount--;
							Correct++;
							PH_DelFig(i);
							update(); // Re-Draw after i delete a fig.
							break;
						}
						else if (figlist[i]->Is_Selected(D))
						{
							mciSendString(TEXT("play wrong.wav"), NULL, 0, NULL);
							Wrong++;
						}
					}
				}
				else
				{
					for (int i = figcount - 1; i >= 0; i--) // start mn el2a5er , 3l4an lw 2 fig drawen on each other
					{
						if (figlist[i]->Is_Selected(D) && !figlist[i]->ISFILLED())
						{
							mciSendString(TEXT("play correct.wav"), NULL, 0, NULL);
							Fcount--;
							Correct++;
							PH_DelFig(i);
							update(); // Re-Draw after i delete a fig.
							break;
						}
						else if (figlist[i]->Is_Selected(D))
						{
							mciSendString(TEXT("play wrong.wav"), NULL, 0, NULL);
							Wrong++;
						}
					}
				}
			}
			pOut->PrintMessage("RightClicks = " + to_string(Correct) + "                   WrongClicks = " + to_string(Wrong) + "                   Remaining Figures = " + to_string(c - Correct));

			// while loop so no need to goto
		}

		//pOut->DrawIMAGE("PH_FillColor", 61, 0, 61, 50);

		if (Wrong>c) // 3l4an el negative (-4/0) :D
		{
			Wrong = c;
		}
		if (c - Wrong == 0)
		{
			mssg = 2;
			PlaySound(NULL, NULL, 0);
			PlaySound("boo.WAV", NULL, SND_ASYNC);
		}
		else if (Correct >= Wrong && Wrong != 0)
		{
			mssg = 1;
			PlaySound(NULL, NULL, 0);
			PlaySound("kids.WAV", NULL, SND_ASYNC);
		}
		else if (Wrong == 0)
		{
			mssg = 3;
			PlaySound(NULL, NULL, 0);
			PlaySound("kids.WAV", NULL, SND_ASYNC);
		}

		for (int i = 3; i > 0; i--)
		{

			switch (mssg)
			{
			case 1:     pOut->PrintMessage("Congratulations , Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
				break;
			case 2:     pOut->PrintMessage("Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
				break;
			case 3:     pOut->PrintMessage("PERFECT SCORE !! Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
				break;

			default:  pOut->PrintMessage("                                 Restarting in " + to_string(i) + " Seconds ...");
				break;
			}
			Sleep(1000);
		}

		PlaySound(NULL, NULL, 0);
		PlaySound("ph.WAV", NULL, SND_LOOP | SND_ASYNC);

}


void PickAndHide:: PH_TypeAndFillMode()
{
	Output* pOut = pManager->GetOutput();
	pOut->DrawIMAGE("PH_BothCE", 122, 0, 61, 50);
	int mssg = 0; // to print the message , look @ the end of the func.
	int filled = 0; // to check if i pressed on a filled fig. , CUZ the base FILLCOLOR will mess with the code
	int selected = 0; // check if i pressed a filled fig or not 
	int s = 700;    // to get the Color
	char w = 'a';    // to get the type
	string q; // to rename the type 
	pManager->PickHideCopy(figlist, figcount);   // creating a new fig. to not affect the main one
	Input* pIn = pManager->GetInput();

	//pOut->CreateToolbar
	pOut->PrintMessage("Searching For Figures Via  ->> Figure Type & Fill Color <<-  , Please Choose a Figure To Start");
	Point D;
f:
	pIn->GetPointClicked(D.x, D.y);	//Get the coordinates of the user click


	if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) // check that he pressed in the Drawing area
	{

		for (int i = figcount - 1; i >= 0; i--)  // 3l4an e5tar elly foo2
		{
			if (figlist[i]->Is_Selected(D) && (figlist[i]->ISFILLED()))
			{
				selected = 1;  // i pressed on a fig
				filled = 1;  // check if i pressed on a filled fig
				s = figlist[i]->GetFillInt(); // know which fill color is it
				w = figlist[i]->GetType(); // know which figure is it , line OR rect OR ...

				switch (w)
				{
				case 'L': q = "Lines";
					break;
				case 'R':  q = "Rectangles";
					break;
				case 'C': q = "Circles";
					break;
				case 'T': q = "Triangles";
					break;

				default:
					goto f;
				}

				switch (s)
				{
				case 0:       pOut->PrintMessage("FILLED !! Pick All BLACK-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 1:        pOut->PrintMessage("FILLED !! Pick All BLUE-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 2:         pOut->PrintMessage("FILLED !! Pick All RED-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 3:       pOut->PrintMessage("FILLED !! Pick All GREEN-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 4:       pOut->PrintMessage("FILLED !! Pick All BROWN-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 5:     pOut->PrintMessage("FILLED !! Pick All BLUEVIOLET-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 6:        pOut->PrintMessage("FILLED !! Pick All CYAN-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 7:      pOut->PrintMessage("FILLED !! Pick All DARKGREEN-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 8:      pOut->PrintMessage("FILLED !! Pick All VIOLET-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 9:        pOut->PrintMessage("FILLED !! Pick All GRAY-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 10:      pOut->PrintMessage("FILLED !! Pick All ORANGE-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 11:        pOut->PrintMessage("FILLED !! Pick All PINK-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 12:    pOut->PrintMessage("FILLED !! Pick All SEAGREEN-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 13:      pOut->PrintMessage("FILLED !! Pick All YELLOW-FILLED " + q + " To Get A Perfect Score..");
					break;
				case 14:      pOut->PrintMessage("FILLED !! Pick All LIGHTSKYBLUE-FILLED " + q + " To Get A Perfect Score..");
					break;

				default:
					goto f;
					break;
				}
				break; // after the switch
			}

			else if (figlist[i]->Is_Selected(D) && !(figlist[i]->ISFILLED()))
			{
				w = figlist[i]->GetType(); // know which figure is it , line OR rect OR ...

				switch (w)
				{
				case 'L': q = "Lines";
					break;
				case 'R':  q = "Rectangles";
					break;
				case 'C': q = "Circles";
					break;
				case 'T': q = "Triangles";
					break;

				default:
					goto f;
				}

				selected = 1;
				s = figlist[i]->GetFillInt(); // know which fill color is it 
				pOut->PrintMessage("NON-FILLED !! Pick All NON-FILLED " + q + " To Get A Perfect Score..");
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
			if ((figlist[i]->GetFillInt() == s) && figlist[i]->ISFILLED() && figlist[i]->GetType() == w)
			{
				Fcount++;
			}
		}
	}

	else
	{
		for (int i = 0; i < figcount; i++)
		{
			if (!(figlist[i]->ISFILLED()) && figlist[i]->GetType() == w )
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
					if (figlist[i]->Is_Selected(D) && figlist[i]->GetType() == w && figlist[i]->ISFILLED() && ( s == figlist[i]->GetFillInt() )  )
					{
						mciSendString(TEXT("play correct.wav"), NULL, 0, NULL);
						Fcount--;
						Correct++;
						PH_DelFig(i);
						update(); // Re-Draw after i delete a fig.
						break;
					}
					else if (figlist[i]->Is_Selected(D))
					{
						mciSendString(TEXT("play wrong.wav"), NULL, 0, NULL);
						Wrong++;
					}
				}
			}
			else
			{
				for (int i = figcount - 1; i >= 0; i--) // start mn el2a5er , 3l4an lw 2 fig drawen on each other
				{
					if (figlist[i]->Is_Selected(D) && figlist[i]->GetType() == w && !figlist[i]->ISFILLED() )
					{
						mciSendString(TEXT("play correct.wav"), NULL, 0, NULL);
						Fcount--;
						Correct++;
						PH_DelFig(i);
						update(); // Re-Draw after i delete a fig.
						break;
					}
					else if (figlist[i]->Is_Selected(D))
					{
						mciSendString(TEXT("play wrong.wav"), NULL, 0, NULL);
						Wrong++;
					}
				}
			}
		}
		pOut->PrintMessage("RightClicks = " + to_string(Correct) + "                   WrongClicks = " + to_string(Wrong) + "                   Remaining Figures = " + to_string(c - Correct));

		// while loop so no need to goto
	}

	//pOut->DrawIMAGE("PH_Both", 122, 0, 61, 50);
	if (Wrong>c) // 3l4an el negative (-4/0) :D
	{
		Wrong = c;
	}
	if (c - Wrong == 0)
	{
		mssg = 2;
		PlaySound(NULL, NULL, 0);
		PlaySound("boo.WAV", NULL, SND_ASYNC);
	}
	else if (Correct >= Wrong && Wrong != 0)
	{
		mssg = 1;
		PlaySound(NULL, NULL, 0);
		PlaySound("kids.WAV", NULL, SND_ASYNC);
	}
	else if (Wrong == 0)
	{
		mssg = 3;
		PlaySound(NULL, NULL, 0);
		PlaySound("kids.WAV", NULL, SND_ASYNC);
	}

	for (int i = 3; i > 0; i--)
	{

		switch (mssg)
		{
		case 1:     pOut->PrintMessage("Congratulations , Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
			break;
		case 2:     pOut->PrintMessage("Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
			break;
		case 3:     pOut->PrintMessage("PERFECT SCORE !! Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
			break;

		default:  pOut->PrintMessage("                                 Restarting in " + to_string(i) + " Seconds ...");
			break;
		}
		Sleep(1000);
	}

	PlaySound(NULL, NULL, 0);
	PlaySound("ph.WAV", NULL, SND_LOOP | SND_ASYNC);


}

void PickAndHide:: PH_AreaMode()
{
	Output* pOut = pManager->GetOutput();
	
	int mssg = 0; // to print the message , look @ the end of the func.
	char s = 'a';    // to get the type
	pManager->PickHideCopy(figlist, figcount);   // creating a new fig. to not affect the main one
	Input* pIn = pManager->GetInput();
	//pOut->CreateToolbar
	pOut->CreatePHAreaToolbar();
	pOut->PrintMessage("Searching For Figures Via ->> Area <<- ,  Select From The TooblBar ( Order (High --> Low) || Order (Low --> High) )  ");
	f:
	int x, y;
	bool ma = false; // to know if order DECEND or ACCEND
	pIn->GetPointClicked(x, y);	//Get the coordinates of the user click
    //[1] If user clicks on the Toolbar
	if (y >= 0 && y < UI.ToolBarHeight)
	{
		//Check whick Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = (x / UI.MenuItemWidth);
		//Divide x coord of the point clicked by the menu item width (int division)
		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
		if (ClickedItemOrder == 2) return;
		if (ClickedItemOrder == 0) { ma = true;    pOut->DrawIMAGE("DECE", 0, 0, 61, 50); }
		else if (ClickedItemOrder == 1) { ma = false;  pOut->DrawIMAGE("ASCCE", 61, 0, 61, 50); }
		else goto f;
	}
	else goto f;
	pOut->PrintMessage("Please Choose A Figure To Start :)");
	G:
	Point D;
	pIn->GetPointClicked(D.x, D.y);
	if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) // check that he pressed in the Drawing area
	{
		for (int i = figcount-1; i >=0; i--)
		{
			if (figlist[i]->Is_Selected(D))
			{
				s = figlist[i]->GetType(); // know which figure is it , line OR rect OR ...
				break;
			}
		}
		if (ma) {
			switch (s)
			{
			case 'L': pOut->PrintMessage("LINE !! Pick All Lines VIA Area In Descending Order (-> From Max To Low <-) ");
				break;
			case 'R':  pOut->PrintMessage("RECTANGLE !! Pick All Rectangles VIA Area In Descending Order (-> From Max To Low <-) ");
				break;
			case 'C': pOut->PrintMessage("CIRCLE !! Pick All Circles VIA Area In Descending Order (-> From Max To Low <-) ");
				break;
			case 'T': pOut->PrintMessage("TRIANGLE !! Pick All Triangles VIA Area In Descending Order (-> From Max To Low <-) ");
				break;
			default:
				goto G;
			}
		}
		else 
		{
			switch (s)
			{
			case 'L': pOut->PrintMessage("LINE !! Pick All Lines VIA Area In Ascending Order (-> From Low To Max <-) ");
				break;
			case 'R':  pOut->PrintMessage("RECTANGLE !! Pick All Rectangles VIA Area In Ascending Order (-> From Low To Max <-) ");
				break;
			case 'C': pOut->PrintMessage("CIRCLE !! Pick All Circles VIA Area In Ascending Order (-> From Low To Max <-) ");
				break;
			case 'T': pOut->PrintMessage("TRIANGLE !! Pick All Triangles VIA Area In Ascending Order (-> From Low To Max <-) ");
				break;
			default:
				goto G;
			}
		}
	}
	else { goto G; } // Didn't press in Draw area
	int Fcount = 0; // When he clicks at a line , this will be the number of all lines , and so on
	int Correct = 0;  // number of correct clicks
	int Wrong = 0;   // number of wrong clicks
	int c = 0;				// for loop to get that number
	if (ma) {
		double max = 0;
		for (int i = 0; i < figcount; i++)
		{
			if (figlist[i]->GetType() == s)
			{
				if (figlist[i]->GetArea() > max) max = figlist[i]->GetArea();
				Fcount++;
			}
		}

	    c = Fcount;
		while (Fcount != 0)
		{
			Point D;
			pIn->GetPointClicked(D.x, D.y);
			if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) // check that he's INSIDE DRAW AREA
			{
				for (int i = figcount - 1; i >= 0; i--) // start mn el2a5er , 3l4an lw 2 fig drawen on each other
				{
					if (figlist[i]->Is_Selected(D) && (int)max ==int( figlist[i]->GetArea()) && figlist[i]->GetType() == s)
					{
						mciSendString(TEXT("play correct.wav"), NULL, 0, NULL);
						Fcount--;
						Correct++;
						PH_DelFig(i);
						update();
						max = 0;
						// Re-Draw after i delete a fig.
						for (int i = 0; i < figcount; i++)
						{
							if (figlist[i]->GetType() == s)
							{
								if (figlist[i]->GetArea() > max) max = figlist[i]->GetArea();
							}
						}
						break;
					}
					else if (figlist[i]->Is_Selected(D))
					{
						mciSendString(TEXT("play wrong.wav"), NULL, 0, NULL);
						Wrong++;
					}
				}
			}
			pOut->PrintMessage("RightClicks = " + to_string(Correct) + "                   WrongClicks = " + to_string(Wrong) + "                   Remaining Figures = " + to_string(c - Correct));
		}
		//pOut->DrawIMAGE("DE", 0, 0, 61, 50);
	}
	else 
	{
		double min = 100000000;
		for (int i = 0; i < figcount; i++)
		{
			if (figlist[i]->GetType() == s)
			{
				if (figlist[i]->GetArea() < min) min = figlist[i]->GetArea();
				Fcount++;
			}
		}

		c = Fcount;
		while (Fcount != 0)
		{
			Point D;
			pIn->GetPointClicked(D.x, D.y);
			if (D.y > UI.ToolBarHeight && D.y < (UI.height - UI.StatusBarHeight)) // check that he's INSIDE DRAW AREA
			{
				for (int i = figcount - 1; i >= 0; i--) // start mn el2a5er , 3l4an lw 2 fig drawen on each other
				{
					if (figlist[i]->Is_Selected(D) && (int)min == (int)figlist[i]->GetArea() && figlist[i]->GetType() == s)
					{
						mciSendString(TEXT("play correct.wav"), NULL, 0, NULL);
						Fcount--;
						Correct++;
						PH_DelFig(i);
						update();
						min= 100000000;
						// Re-Draw after i delete a fig.
						for (int i = 0; i < figcount; i++)
						{
							if (figlist[i]->GetType() == s)
							{
								if (figlist[i]->GetArea() < min) min = figlist[i]->GetArea();
							}
						}
						break;
					}
					else if (figlist[i]->Is_Selected(D))
					{
						mciSendString(TEXT("play wrong.wav"), NULL, 0, NULL);
						Wrong++;
					}
				}
			}
			pOut->PrintMessage("RightClicks = " + to_string(Correct) + "                   WrongClicks = " + to_string(Wrong) + "                   Remaining Figures = " + to_string(c - Correct));
		}
		//pOut->DrawIMAGE("ASC", 61, 0, 61, 50);
	}
	

	if (Wrong>c) // 3l4an el negative (-4/0) :D
	{
		Wrong = c;
	}
	if (c - Wrong == 0)
	{
		mssg = 2;
		PlaySound(NULL, NULL, 0);
		PlaySound("boo.WAV", NULL, SND_ASYNC);
	}
	else if (Correct >= Wrong && Wrong != 0)
	{
		mssg = 1;
		PlaySound(NULL, NULL, 0);
		PlaySound("kids.WAV", NULL, SND_ASYNC);
	}
	else if (Wrong == 0)
	{
		mssg = 3;
		PlaySound(NULL, NULL, 0);
		PlaySound("kids.WAV", NULL, SND_ASYNC);
	}

	for (int i = 3; i > 0; i--)
	{

		switch (mssg)
		{
		case 1:     pOut->PrintMessage("Congratulations , Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
			break;
		case 2:     pOut->PrintMessage("Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
			break;
		case 3:     pOut->PrintMessage("PERFECT SCORE !! Your Score Is " + to_string(c - Wrong) + "/" + to_string(c) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
			break;

		default:  pOut->PrintMessage("                                 Restarting in " + to_string(i) + " Seconds ...");
			break;
		}
		Sleep(1000);
	}

	PlaySound(NULL, NULL, 0);
	PlaySound("ph.WAV", NULL, SND_LOOP | SND_ASYNC);

}
