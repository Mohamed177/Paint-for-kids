#include "ApplicationManager.h"
#include"Actions\AddLineAction.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\SaveAction.h"
#include "Actions\SelectAction.h"
#include "Actions\ZoomInAction.h"
#include"Actions\ZoomOutAction.h"
#include "Actions\ResizeAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\ChngBrdrWdth.h"
#include"Actions\SwtchTOplay.h"
#include"Actions\SwtchTOdraw.h"
#include"Figures\CCircle.h"
#include"Figures\CLine.h"
#include"Figures\CRectangle.h"
#include"Figures\CTriangle.h"
#include "Actions\ChngBackClr.h"
#include"Actions\ChngDrwClr.h"
#include"Actions\ChngFillClr.h"
#include "Actions\ExitAction.h"
#include "CMUgraphicsLib\colors.h"
#include "Actions\LoadAction.h"
#include"Actions\MoveAction.h"
#include"Actions\CopyAction.h"
#include"Actions\CutAction.h"
#include"Actions\PasteAction.h"
#include "Actions\Scramble.h"
#include <fstream>

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	Saved = false;
	FigCount = 0;
	Ccount = 0;
	Zcount = 0;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
	{
		FigList[i] = NULL;
		CopyList[i] = NULL;
		ZoomList[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;
		case COPY:
			pAct = new CopyAction(this);
			break;
		case CUT:
			pAct = new CutAction(this);
			break;

		case PASTE:
			pAct = new PasteAction(this);
			break;

		case DRAW_LINE:
			pAct = new AddLineAction(this);

			break;
		case DRAW_TRI:
			pAct = new AddTriAction(this);

			break;
		case DRAW_CIRC:
			pAct = new AddCircAction(this);
			break;

		case SAVE:
			pAct = new SaveAction(this);
			break;

		case LOAD:
			pAct = new LoadAction(this);
			break;

		case TO_SELECT:
			pAct = new SelectAction(this);
			break;

		case ZOOMIN:
			pAct = new ZoomIn(this);
			break;

		case ZOOMOUT:
			pAct = new ZoomOutAction(this);
			break;

		case RESIZE:
			pAct = new ResizeAction(this);
			break;

		case CHNG_BK_CLR:
			pAct = new ChngBackClr(this);
			break;

		case DEL:
			pAct = new DeleteAction(this);
			break;
		case MOVE:
			pAct = new MoveAction(this);
			break;
		case EXIT:
			pAct = new ExitAction(this);
			break;
		case TO_PLAY:
			pAct = new SwtchTOplay(this);
			break;
		case TO_DRAW:
			pAct = new SwtchTOdraw(this);
			break;
		case CHNG_BRDR_WDTH:
			pAct = new ChngBrdrWdth(this);
			break;
		case CHNG_DRAW_CLR:
			pAct = new ChangeDrawColor(this);
			break;
		case CHNG_FILL_CLR:
			pAct = new ChangeFillColor(this);
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const   //by: Riad Adel
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	Point P;
	P.x = x;
	P.y = y;
	for (int i = FigCount-1; i >= 0; i--)
	{
		if (FigList[i ]->Is_Selected(P))
		{

			return FigList[i];
		}
	}

	///Add your code here to search for a figure given a point x,y	

	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface(ActionType act) const
{
	pOut->ClearDrawArea();
	if (act == ZOOMIN || act == ZOOMOUT)
	{
		for (int i = 0; i < FigCount; i++)
			ZoomList[i]->Draw(pOut);
		pOut->CreateDrawToolBar();
		pOut->ClearStatusBar();
	}
	else 
		for(int i=0; i<FigCount; i++)
			FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}


void ApplicationManager::SaveAll(ofstream &OutFile) const
{
	string drwcolor = UI.DrawColor, fllclr = UI.FillColor, bckclr = UI.BkGrndColor;
	OutFile << (string)UI.DrawColor << ' ' << (string)UI.FillColor << ' ' << (string)UI.BkGrndColor << endl << FigCount << endl;
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Save(OutFile);
}
void ApplicationManager::LoadAll(ifstream &LoadFile) 
{
	Point p;
	p.x = 0;
	p.y = 0;
	GfxInfo Gfx;
	Gfx.BorderWdth = 1; Gfx.DrawClr = BLACK; Gfx.FillClr = BLACK; Gfx.isFilled = false;
	if (FigCount != 0) 
	{
		Action* pAct = new SaveAction(this);
		pAct->Execute();
		delete pAct;
	}
	FigCount = 0;
	int x = 0;
	string a, b, c;
	LoadFile >> a >> b >> c;
	UI.DrawColor = a;
	UI.FillColor = b;
	UI.BkGrndColor = c;
	LoadFile >> x;
	for (int  i = 0; i < x; i++)
	{
		string s = "";
		LoadFile >> s;
		switch (s[0])
		{
		case 'L' :
			FigList[i] = new CLine( p , p , Gfx);
			break;
		case 'R':
			FigList[i] = new CRectangle( p , p , Gfx);
			break;
		case 'T':
			FigList[i] = new CTriangle(p , p , p , Gfx);
			break;
		case 'C':
			FigList[i] = new CCircle(p , 0, Gfx);
			break;
		default:
			break;
		}
		FigList[i]->Load(LoadFile);
		FigCount++;
	}

}

void ApplicationManager::ResizeSelected(float factor)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
			FigList[i]->Resize(factor);
	}
}

void ApplicationManager::Delete_Figs()
{
	int i = 0;
	while (i < FigCount)
	{
		if (FigList[i]->IsSelected())
		{
			delete FigList[i];
			FigList[i] = NULL;
			for (int j = i; j < FigCount-1; j++)
			{
				swap(FigList[j], FigList[j+1]);
			}
			FigCount--;
		}
		else
		{
			i++;
		}
	}
}
void ApplicationManager::Copy() 
{
	for (int  i = 0; i < Ccount; i++)
	{
		delete CopyList[i];
		CopyList[i] = NULL;
	}
	Ccount = 0;
	for (int  i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			CopyList[Ccount++] = FigList[i]->copy();
		}
	}
}
void ApplicationManager::ZoomCopy()
{
	if (Zcount == 0)
	{
		for (int i = 0; i < Zcount; i++)
		{
			delete ZoomList[i];
			ZoomList[i] = NULL;
		}
		for (int i = 0; i < FigCount; i++)
		{
			ZoomList[i] = FigList[i]->copy();
		}
	}
}

void ApplicationManager::Zoom(float factor)
{
	for (int i = 0; i < FigCount; i++)
	{
		ZoomList[i]->Zoom(factor);
	}
}

void ApplicationManager::Cut() 
{
	for (int i = 0; i < Ccount; i++)
	{
		delete CopyList[i];
		CopyList[i] = NULL;
	}
	Ccount = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			CopyList[Ccount++] = FigList[i]->copy();
			delete FigList[i];
			FigList[i] = NULL;
			for (int j = i; j < FigCount - 1; j++)
			{
				swap(FigList[j], FigList[j + 1]);
			}
			FigCount--;
			i--;
		}
	}
}
bool  ApplicationManager::move( Point v ) 
{
	Point Center;
	int count = 0;
	for (int  i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			Point p = FigList[i]->GetCenter();
			Center.x += p.x;
			Center.y += p.y;
			count++;
		}
	}
	if (count != 0) {
		Center.x = (Center.x) / count;
		Center.y = (Center.y) / count;
	}
	v.x = (-Center.x + v.x);
	v.y = (-Center.y + v.y);
	bool t = true;
	for (int  i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			if (!(FigList[i]->ValidMove(v)))
			{
				t = false;
				break;
			}
		}
	}
	if (!t)
	{
		return false;
	}
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->Move(v);
		}
	}
	return true;

}

void ApplicationManager::ScrambleMove()
{
	Point Center;
	Point v;
	v.x = UI.width / 4;
	v.y = UI.height / 2;
	int count = 0;
	for (int i = 0; i < Zcount; i++)
	{
		Point p = ZoomList[i]->GetCenter();
		Center.x += p.x;
		Center.y += p.y;
		count++;
	}
	if (count != 0) {
		Center.x = (Center.x) / count;
		Center.y = (Center.y) / count;
	}
	
	v.x = (-Center.x + v.x);
	v.y = (-Center.y + v.y);
	for (int i = 0; i < Zcount; i++)
	{
			ZoomList[i]->Move(v);
	}
}

//------ Get Fig Counter 
int ApplicationManager::GetFig_Counter()
{
	return FigCount;
}

//-------------------- Paste Function
bool ApplicationManager::paste(Point v)
{
	Point Center;
	int count = 0;
	if (Ccount==0)
	{
		pOut->PrintMessage("No Figures to Paste");
		Sleep(1000);
		return false;
	}
	for (int i = 0; i < Ccount; i++)
	{
			Point p = CopyList[i]->GetCenter();
			Center.x += p.x;
			Center.y += p.y;
			count++;
	}
	if (count != 0) {
		Center.x = (Center.x) / count;
		Center.y = (Center.y) / count;
	}
	v.x = (-Center.x + v.x);
	v.y = (-Center.y + v.y);
	bool t = true;
	for (int i = 0; i < Ccount; i++)
	{
		if (!(CopyList[i]->ValidMove(v)))
		{		
			t = false;
			break;
		}
		
	}
	if (!t)
	{
		return false;
	}
	int temp_counter = FigCount;
	for (int i = 0; i < Ccount; i++)
	{
		FigList[FigCount++] =CopyList[i]->copy();
	}
	for (int i = temp_counter; i < FigCount; i++)
	{
		FigList[i]->Move(v);
	}

}

//-------------------- Switch To Play Mode Function
void ApplicationManager::switchtoplay()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected()) FigList[i]->SetSelected(false);
	}
}


//-------------------- Change Border Width Function
void ApplicationManager::ChngeBrdrWdth()
{
f:
	int x, y;
	pIn->GetPointClicked(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			if (ClickedItemOrder > 11) goto f;
			if (ClickedItemOrder == 11)
			{
				pOut->ClearToolBar();
				pOut->CreateDrawToolBar();
				return;
			}

			int brdr[11] = { 1,2,4,6,8,10,12,14,16,18,20 };

			bool flag = false;
			for (int i = 0; i < FigCount; i++)
			{
				if (FigList[i]->IsSelected())
				{
					flag = true;
					FigList[i]->ChngBrdWdt(brdr[ClickedItemOrder]);
				}
			}
			if (!flag) pOut->setCrntPenWidth(brdr[ClickedItemOrder]);

		}
		else goto f;
		pOut->CreateDrawToolBar();
		

	}
}


//-------------------- Change Draw Color Function
void ApplicationManager:: ChangeDrwColor()
{
	bool flag = false; // to check if ther is any selected figs.
	color c;
	
f:
	int x, y;
	pIn->GetPointClicked(x, y);	           //Get the coordinates of the user click
	if (y >= 0 && y < UI.ToolBarHeight)
	{
		//Check whick Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = (x / UI.MenuItemWidth);
		//Divide x coord of the point clicked by the menu item width (int division)
		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

		if (ClickedItemOrder == 14) return; // back button pressed.
		
		// else , getting the pressed color.
	    c = SNOW;
		switch (ClickedItemOrder)
		{
		case ITM_BLACK: { c = BLACK;   }
						break;
		case ITM_BLUE: { c = BLUE; }
					   break;
		case ITM_RED: {  c = RED; }
					  break;
		case ITM_GREEN: { c = GREEN; }
						break;
		case ITM_BROWN: { c = BROWN; }
						break;
		case ITM_BLUEVIOLET: {  c = BLUEVIOLET; }
							 break;
		case ITM_CYAN: { c = CYAN; }
					   break;
		case ITM_DARKGREEN: { c = DARKGREEN; }
							break;
		case ITM_VIOLET: {  c = VIOLET; }
						 break;
		case ITM_GRAY: { c = GRAY; }
					   break;
		case ITM_ORANGE: { c = ORANGE; }
						 break;
		case ITM_PINK: {  c = PINK; }
					   break;
		case ITM_SEAGREEN: { c = SEAGREEN; }
						   break;
		case ITM_YELLOW: { c = YELLOW; }
						 break;
		default:goto f;
		}
		
	}
	else // in the user didn't press in the tool bar
	{
		goto f;
	}


	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			flag = true;
			FigList[i]->ChngDrawClr(c);
		}
	}
	if (!flag) UI.DrawColor = c;
	
}


//-------------------- Change Fill Color Function
void ApplicationManager::ChangeFllColor()
{
	bool flag = false; // to check if there is any selected figs.
	color c;

f:
	int x, y;
	pIn->GetPointClicked(x, y);	           //Get the coordinates of the user click
	if (y >= 0 && y < UI.ToolBarHeight)
	{
		//Check whick Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = (x / UI.MenuItemWidth);
		//Divide x coord of the point clicked by the menu item width (int division)
		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

		if (ClickedItemOrder == 14) return; // back button pressed.

											
							// else , getting the pressed color.
		c = SNOW;
		switch (ClickedItemOrder)
		{
		case ITM_BLACK: { c = BLACK;   }
						break;
		case ITM_BLUE: { c = BLUE; }
					   break;
		case ITM_RED: {  c = RED; }
					  break;
		case ITM_GREEN: { c = GREEN; }
						break;
		case ITM_BROWN: { c = BROWN; }
						break;
		case ITM_BLUEVIOLET: {  c = BLUEVIOLET; }
							 break;
		case ITM_CYAN: { c = CYAN; }
					   break;
		case ITM_DARKGREEN: { c = DARKGREEN; }
							break;
		case ITM_VIOLET: {  c = VIOLET; }
						 break;
		case ITM_GRAY: { c = GRAY; }
					   break;
		case ITM_ORANGE: { c = ORANGE; }
						 break;
		case ITM_PINK: {  c = PINK; }
					   break;
		case ITM_SEAGREEN: { c = SEAGREEN; }
						   break;
		case ITM_YELLOW: { c = YELLOW; }
						 break;
		default:goto f;
		}

	}
	else // in the user didn't press in the tool bar
	{
		goto f;
	}

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			flag = true;
			FigList[i]->ChngFillClr(c);
		}
	}
	if (!flag) UI.FillColor = c;
	
}


