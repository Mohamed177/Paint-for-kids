#include "CLine.h"

CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	p1 = P1;
	p2 = P2;
}


void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawLine to draw a Line on the screen	
	pOut->DrawLINE(p1, p2, FigGfxInfo, Selected);
}

bool CLine::Is_Selected(Point P) const
{
	bool b = false;
	// check if the point lies on the line 
	//using a "cross-product" of vectors point1 -> Point and point1 -> point2.
	// if (((P.x >= p1.x & P.x <= p2.x) || (P.x <= p1.x && P.x >= p2.x) ) && ((P.y >= p1.y & P.y <= p2.y) || (P.y <= p1.y && P.y >= p2.y))) {
	int dxc = P.x - p1.x;
	int dyc = P.y - p1.y;

	int dxl = p2.x - p1.x;
	int dyl = p2.y - p1.y;

	int cross = dxc * dyl - dyc * dxl;
	// point lies on the line if and only if cross is equal to zero.
	if ((abs(cross)) <= 1000)
		b = true;
	else b = false;
	//}
	//return false;
	//check if the point is BETWEEN p1 & p2
	//This can be easily done by comparing the x coordinates,
	//if the line is "more horizontal than vertical", or y coordinates otherwise

	if ((abs(dxl) >= abs(dyl)) && (b))
		return dxl > 0 ?
		p1.x <= P.x && P.x <= p2.x :
		p2.x <= P.x && P.x <= p1.x;
	else if ((b) && (abs(dxl) < abs(dyl)))
		return dyl > 0 ?
		p1.y <= P.y && P.y <= p2.y :
		p2.y <= P.y && P.y <= p1.y;

}



void CLine::Save(ofstream &OutFile)
{
	OutFile << "Line " << ID << ' ' << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << ' ' << FigGfxInfo.BorderWdth << ' ' << (string)FigGfxInfo.DrawClr << " \n";
}

CLine::~CLine()
{

}
void CLine::Zoom(float factor)
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
	ChngBrdWdt(ceil(FigGfxInfo.BorderWdth*factor));
	Resize(factor, true);
	Move(p);
}
void CLine::PrintInfo(Output * pOut)
{
	string info = "Line of ID : " + to_string(ID) + " Point 1 : ( " + to_string(p1.x) + " , " + to_string(p1.y);
	info += " ) Point 2 : ( " + to_string(p2.x) + " , " + to_string(p2.y) + " ) ";
	string Color = FigGfxInfo.DrawClr;
	info += Color;
	pOut->PrintMessage(info);
}
void CLine::Load(ifstream &Infile) 
{
	string drwColor;
	Infile >> ID >> p1.x >> p1.y >> p2.x >> p2.y >> FigGfxInfo.BorderWdth >> drwColor;
	FigGfxInfo.DrawClr = drwColor;
}
 Point CLine::GetCenter() 
{
	 Point v;
	 v.x = (p1.x + p2.x) / 2;
	 v.y = (p1.y + p2.y) / 2;
	 return v;

}

void CLine::Resize(float factor, bool zoom = false)
{
	Point mid, temp1 = p1, temp2 = p2;
	mid.x = (p1.x + p2.x) / 2;
	mid.y = (p1.y + p2.y) / 2;
	while (factor < 1)
	{
		p1.x = (p1.x + mid.x) / 2;
		p1.y = (p1.y + mid.y) / 2;
		p2.x = (p2.x + mid.x) / 2;
		p2.y = (p2.y + mid.y) / 2;
		factor *= 2;
	}
	while (factor > 1)
	{
		p1.x = p1.x * 2 - mid.x;
		p1.y = p1.y * 2 - mid.y;
		p2.x = p2.x * 2 - mid.x;
		p2.y = p2.y * 2 - mid.y;
		factor /= 2;
	}
	if (!zoom)
		if (p1.x < 0 || p1.x > UI.width || p1.y < 0 || p1.y > UI.height || p2.x < 0 || p2.x > UI.width || p2.y < 0 || p2.y > UI.height)
		{
			p1 = temp1;
			p2 = temp2;
		}
}

bool CLine::ValidMove(Point p, bool scramble = 0) 
{
	Point v1, v2;
	v1.x = p1.x + p.x;
	v1.y = p1.y + p.y;
	v2.x = p2.x + p.x;
	v2.y = p2.y + p.y;
	int left_border = 0;
	if (scramble)
		left_border = UI.width / 2;
	if ((v1.y > UI.ToolBarHeight && v2.y > UI.ToolBarHeight && v1.y < (UI.height - UI.StatusBarHeight) && v2.y < (UI.height - UI.StatusBarHeight) && v1.x <= UI.width &&v2.x <= UI.width && v1.x>=left_border &&v2.x >=left_border))
	{
		return true;
	}
	return false;
}
CFigure * CLine::copy() 
{
	CLine *L = new CLine(p1, p2, FigGfxInfo);
	CFigure * v = L;
	return v;

}

void CLine::Move(Point v)
{
	p1.x += v.x;
	p1.y += v.y;
	p2.x += v.x;
	p2.y += v.y;
}



char CLine::GetType()
{
	return 'L';
}

double CLine::GetArea()
{
	return sqrt((abs(p1.x-p2.x)*abs(p1.x - p2.x)) + (abs(p1.y - p2.y)*abs(p1.y - p2.y)));
}






