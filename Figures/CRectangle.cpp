#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

bool CRectangle::Is_Selected(Point P) const
{
	int minX, minY, maxX, maxY;
	if (Corner1.x >= Corner2.x)
	{
		maxX = Corner1.x;
		minX = Corner2.x;
	}
	else 
	{
		minX = Corner1.x;
		maxX = Corner2.x;
	}
	if (Corner1.y >= Corner2.y)
	{
		maxY = Corner1.y;
		minY = Corner2.y;
	}
	else
	{
		minY = Corner1.y;
		maxY = Corner2.y;
	}
	if (P.x >= minX && P.x <= maxX && P.y >= minY && P.y <= maxY )
		return true;
	return false;
}

void CRectangle::Save(ofstream &OutFile)
{
	OutFile << "Rectangle " << ID << ' ' << Corner1.x << ' ' << Corner1.y << ' ' << Corner2.x << ' ' << Corner2.y << ' ';
	if (FigGfxInfo.DrawClr == BLACK)
		OutFile << "BLACK ";
	else if (FigGfxInfo.DrawClr == BLUE)
		OutFile << "BLUE ";
	else if (FigGfxInfo.DrawClr == RED)
		OutFile << "RED ";
	else if (FigGfxInfo.DrawClr == DARKGREEN)
		OutFile << "DARKGREEN ";
	else if (FigGfxInfo.DrawClr == GREEN)
		OutFile << "GREEN ";
	else if (FigGfxInfo.DrawClr == BROWN)
		OutFile << "BROWN ";
	else if (FigGfxInfo.DrawClr == BLUEVIOLET)
		OutFile << "BLUEVIOLET ";
	else if (FigGfxInfo.DrawClr == CYAN)
		OutFile << "CYAN ";
	else if (FigGfxInfo.DrawClr == VIOLET)
		OutFile << "VIOLET ";
	else if (FigGfxInfo.DrawClr == GRAY)
		OutFile << "GRAY ";
	else if (FigGfxInfo.DrawClr == ORANGE)
		OutFile << "ORANGE ";
	else if (FigGfxInfo.DrawClr == PINK)
		OutFile << "PINK ";
	else if (FigGfxInfo.DrawClr == SEAGREEN)
		OutFile << "SEAGREEN ";
	else if (FigGfxInfo.DrawClr == YELLOW)
		OutFile << "YELLOW ";
	if (FigGfxInfo.isFilled)
		OutFile << "NO_FILL\n";
	else
	{
		if (FigGfxInfo.FillClr == BLACK)
			OutFile << "BLACK\n";
		else if (FigGfxInfo.FillClr == BLUE)
			OutFile << "BLUE\n";
		else if (FigGfxInfo.FillClr == RED)
			OutFile << "RED\n";
		else if (FigGfxInfo.FillClr == DARKGREEN)
			OutFile << "DARKGREEN\n";
		else if (FigGfxInfo.FillClr == GREEN)
			OutFile << "GREEN\n";
		else if (FigGfxInfo.FillClr == BROWN)
			OutFile << "BROWN\n";
		else if (FigGfxInfo.FillClr == BLUEVIOLET)
			OutFile << "BLUEVIOLET\n";
		else if (FigGfxInfo.FillClr == CYAN)
			OutFile << "CYAN\n";
		else if (FigGfxInfo.FillClr == VIOLET)
			OutFile << "VIOLET\n";
		else if (FigGfxInfo.FillClr == GRAY)
			OutFile << "GRAY\n";
		else if (FigGfxInfo.FillClr == ORANGE)
			OutFile << "ORANGE\n";
		else if (FigGfxInfo.FillClr == PINK)
			OutFile << "PINK\n";
		else if (FigGfxInfo.FillClr == SEAGREEN)
			OutFile << "SEAGREEN\n";
		else if (FigGfxInfo.FillClr == YELLOW)
			OutFile << "YELLOW\n";
		if (FigGfxInfo.isFilled)
			OutFile << "NO_FILL\n";
	}
}