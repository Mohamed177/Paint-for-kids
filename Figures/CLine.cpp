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

	// check if the point lies on the line 
	//using a "cross-product" of vectors point1 -> Point and point1 -> point2.
	int dxc = P.x - p1.x;
	int dyc = P.y - p1.y;

	int dxl = p2.x - p1.x;
	int dyl = p2.y - p1.y;

	int cross = dxc * dyl - dyc * dxl;
	// point lies on the line if and only if cross is equal to zero.
	if (cross == 0)
		return true;
	return false;

	//check if the point is BETWEEN p1 & p2
	//This can be easily done by comparing the x coordinates,
	//if the line is "more horizontal than vertical", or y coordinates otherwise

	if (abs(dxl) >= abs(dyl))
		return dxl > 0 ?
		p1.x <= P.x && P.x <= p2.x :
		p2.x <= P.x && P.x <= p1.x;
	else
		return dyl > 0 ?
		p1.y <= P.y && P.y <= p2.y :
		p2.y <= P.y && P.y <= p1.y;

}

void CLine::Save(ofstream &OutFile)
{
	OutFile << "Line " << ID << ' ' << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << ' ';

}
CLine::~CLine()
{

}