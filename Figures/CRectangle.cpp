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
	OutFile << FigGfxInfo.DrawClr;
	if (FigGfxInfo.isFilled)
		OutFile << FigGfxInfo.FillClr << endl;
	else 
		OutFile << "NO_FILL\n";
}

void CRectangle::Resize(float factor)
{
	Point mid13, mid14, Corner3, Corner4;

	Corner3.y = Corner1.y;
	Corner3.x = Corner2.x;

	Corner4.x = Corner1.x;
	Corner4.y = Corner2.y;

	mid13.x = (Corner1.x + Corner2.x) / 2;
	mid14.y = Corner1.y;

	mid14.x = Corner1.x;
	mid14.y = (Corner1.y + Corner2.y) / 2;

	int side13 = sqrt((Corner1.x - Corner3.x)*(Corner1.x - Corner3.x) + (Corner1.y - Corner3.y)*(Corner1.y - Corner3.y)) * factor / 2;
	int side14 = sqrt((Corner1.x - Corner4.x)*(Corner1.x - Corner4.x) + (Corner1.y - Corner4.y)*(Corner1.y - Corner4.y)) * factor / 2;

	bool chk1, chk2, chk3, chk4;
	chk1 = (mid13.x - side13 >= 0);
	chk2 = (mid13.x + side13 <= UI.width);
	chk3 = (mid14.y - side14 >= 0);
	chk4 = (mid14.y + side14 <= (UI.height - UI.StatusBarHeight - UI.ToolBarHeight));
	if (chk1 && chk2 && chk3 && chk4)
	{
		if (Corner1.x != Corner2.x)
			if (Corner1.x < Corner2.x)
			{
				if (mid13.x - side13 >= 0)
				{
					Corner1.x = mid13.x - side13;
					Corner2.x = mid13.x + side13;
				}
				//else 
					// cant resize
			}
			else
			{
				if (mid13.x + side13 <= UI.width)
				{
					Corner1.x = mid13.x + side13;
					Corner2.x = mid13.x - side13;
				}
				//else
			}
		if (Corner1.y != Corner2.y)
			if (Corner1.y < Corner2.y)
			{
				if (mid14.y - side14 >= 0)
				{
					Corner1.y = mid14.y - side14;
					Corner2.y = mid14.y + side14;
				}
				//else 
				// cant resize
			}
			else
			{
				if (mid14.y + side14 <= (UI.height - UI.StatusBarHeight - UI.ToolBarHeight))
				{
					Corner2.y = mid14.y - side14;
					Corner1.y = mid14.y + side14;
				}
				//else
			}
	}
}