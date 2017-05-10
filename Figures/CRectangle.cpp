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
	OutFile << (string)FigGfxInfo.DrawClr;
	if (FigGfxInfo.isFilled)
		OutFile << ' ' << (string)FigGfxInfo.FillClr << endl;
	else 
		OutFile << " NO_FILL\n";
}

void CRectangle::Resize(float factor, bool zoom = false)
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
	if (!zoom)
	{
		if (chk1 && chk2 && chk3 && chk4)
		{
			if (Corner1.x != Corner2.x)
				if (Corner1.x < Corner2.x)
				{
					Corner1.x = mid13.x - side13;
					Corner2.x = mid13.x + side13;
				}
				else
				{
					Corner1.x = mid13.x + side13;
					Corner2.x = mid13.x - side13;
				}
			if (Corner1.y != Corner2.y)
				if (Corner1.y < Corner2.y)
				{
					Corner1.y = mid14.y - side14;
					Corner2.y = mid14.y + side14;
				}
				else
				{
					Corner1.y = mid14.y + side14;
					Corner2.y = mid14.y - side14;
				}
		}
	}
	else
	{
		if (Corner1.x != Corner2.x)
			if (Corner1.x < Corner2.x)
			{
				Corner1.x = mid13.x - side13;
				Corner2.x = mid13.x + side13;
			}
			else
			{
				Corner1.x = mid13.x + side13;
				Corner2.x = mid13.x - side13;
			}
		if (Corner1.y != Corner2.y)
			if (Corner1.y < Corner2.y)
			{
				Corner1.y = mid14.y - side14;
				Corner2.y = mid14.y + side14;
			}
			else
			{
				Corner1.y = mid14.y + side14;
				Corner2.y = mid14.y - side14;
			}
	}
}

void CRectangle::PrintInfo(Output* pOut)
{
	string info = "Rectangle of ID : " + to_string(ID) + " Corner 1 : ( " + to_string(Corner1.x) + " , " + to_string(Corner1.y);
	info += " ) Conrer 2 : ( " + to_string(Corner2.x) + " , " + to_string(Corner2.y);
	string Color = FigGfxInfo.DrawClr;
	if (FigGfxInfo.isFilled)
		Color += " No Fill.";
	else
		Color += FigGfxInfo.FillClr;
	info += Color;
	pOut->PrintMessage(info);
}

void CRectangle::Load(ifstream &Infile)
{
	string drwColor, Fcolor;
	Infile >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> drwColor >> Fcolor;
	FigGfxInfo.DrawClr = drwColor;
	if (Fcolor == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = Fcolor;
	}
}

void CRectangle::Move(Point nCorner)
{
	Corner1.x += nCorner.x;
	Corner1.y += nCorner.y;
	Corner2.x += nCorner.x;
	Corner2.y += nCorner.y;
} 

Point CRectangle::GetCenter() 
{
	Point v;
	v.x = (Corner1.x + Corner2.x) / 2;
	v.y = (Corner1.y + Corner2.y) / 2;
	return v;

}
bool CRectangle::ValidMove(Point p) 
{
	Point v1, v2;
	v1.x = Corner1.x + p.x;
	v1.y = Corner1.y + p.y;
	v2.x = Corner2.x + p.x;
	v2.y = Corner2.y + p.y;
		if ((v1.y > UI.ToolBarHeight && v2.y > UI.ToolBarHeight && v1.y < (UI.height - UI.StatusBarHeight) && v2.y < (UI.height - UI.StatusBarHeight) &&  v1.x <= UI.width &&v2.x <= UI.width&&  v1.x >=0 &&v2.x >=0))
		{
			return true;
		}
	return false;
}
CFigure * CRectangle::copy() 
{
	CRectangle *R = new CRectangle(Corner1, Corner2, FigGfxInfo);
	CFigure * v = R;
	return v;
}

void CRectangle::Zoom(float factor)
{
	Point wcenter, p, Center;
	Center = GetCenter();
	wcenter.x = UI.width / 2;
	wcenter.y = UI.height / 2;
	if (factor > 1)
	{
		p.x = Center.x - wcenter.x;
		p.y = Center.y - wcenter.y;
	}
	else
	{
		p.x = wcenter.x - Center.x;
		p.y = wcenter.y - Center.y;
		p.x *= 1.0 - factor;
		p.y *= 1.0 - factor;
	}
	Resize(factor,true);
	Move(p);
}
