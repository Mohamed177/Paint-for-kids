#include "CFigure.h"

int CFigure::counter = 1;
CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID = counter;
	counter++;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

bool CFigure::ISFILLED() const
{
	return FigGfxInfo.isFilled;
}








void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::ChngBrdWdt(int p)
{
	FigGfxInfo.BorderWdth = p;
}

int CFigure::GetFillInt() const
{
	if (FigGfxInfo.FillClr == BLACK)
		return 0;
	else if (FigGfxInfo.FillClr == BLUE)
		return 1;
	else if (FigGfxInfo.FillClr == RED)
		return 2;
	else if (FigGfxInfo.FillClr == GREEN)
		return 3;
	else if (FigGfxInfo.FillClr == BROWN)
		return 4;
	else if (FigGfxInfo.FillClr == BLUEVIOLET)
		return 5;
	else if (FigGfxInfo.FillClr == CYAN)
		return 6;
	else if (FigGfxInfo.FillClr == DARKGREEN)
		return 7;
	else if (FigGfxInfo.FillClr == VIOLET)
		return 8;
	else if (FigGfxInfo.FillClr == GRAY)
		return 9;
	else if (FigGfxInfo.FillClr == ORANGE)
		return 10;
	else if (FigGfxInfo.FillClr == PINK)
		return 11;
	else if (FigGfxInfo.FillClr == SEAGREEN)
		return 12;
	else if (FigGfxInfo.FillClr == YELLOW)
		return 13;
	else if (FigGfxInfo.FillClr == LIGHTSKYBLUE)
		return 14; 
	else if (FigGfxInfo.FillClr == LIGHTGOLDENRODYELLOW)
		return 46; 
	
}

int CFigure::getID()
{
	return ID;
}

void CFigure::setID(int i)
{
	ID = i;
}
