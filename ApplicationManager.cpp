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
#include"Figures\CCircle.h"
#include"Figures\CLine.h"
#include"Figures\CRectangle.h"
#include"Figures\CTriangle.h"
#include <fstream>
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
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

		case DEL:
			pAct = new DeleteAction(this);
			break;

		case EXIT:
			///create ExitAction here
			
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
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i ]->Is_Selected(P))
		{
			return FigList[i ];
		}
	}

	///Add your code here to search for a figure given a point x,y	

	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
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
	color Draw, fill, background;
	int x = 0;
	//LoadFile >> Draw >> fill >> background;
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
			FigList[i] = new CCircle(p , p , Gfx);
			break;
		default:
			break;
		}
		//FigList[i]->Load(LoadFile);
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
//------ Get Fig Counter 
int ApplicationManager::GetFig_Counter()
{
	return FigCount;
}
