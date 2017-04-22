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