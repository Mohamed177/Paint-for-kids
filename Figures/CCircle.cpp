#include "CCircle.h"

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	
	this->P2 = P2;
}
void CCircle::Draw(Output *pOut) const
{
	double Raduis = sqrt(((P2.y - Center.y) *(P2.y - Center.y)) + ((P2.x - Center.x)*(P2.x - Center.x)));
	pOut->DrawCIRC(Center, Raduis, FigGfxInfo, Selected);
}

bool CCircle::Is_Selected(Point P) const
{
	double Raduis = sqrt(((P2.y - Center.y) *(P2.y - Center.y)) + ((P2.x - Center.x)*(P2.x - Center.x)));
	if ((P.x*P.x + P.y * P.y) <= (Raduis*Raduis))
	{
		return true;
	}
	return false;
}
