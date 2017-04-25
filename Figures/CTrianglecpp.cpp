#include "CTriangle.h"



CTriangle::CTriangle(Point P1 , Point P2 , Point P3 , GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	p1 = P1;
	p2 = P2;
	p3 = P3;
}
void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DraTRI to draw a rectangle on the screen	
	pOut->DrawTRI(p1 , p2 , p3 , FigGfxInfo, Selected);
}
bool CTriangle::Is_Selected(Point v) const 
{
	Point p1v = pPoint(p1, v);
	Point p2v = pPoint(p2, v);
	Point p3v = pPoint(p3, v);
	Point p1p2 = pPoint(p1, p2);
	Point p2p3 = pPoint(p2, p3);
	Point p3p1 = pPoint(p3, p1);
	int A = CrossProuct(p1v, p1p2);
	int B = CrossProuct(p2v, p2p3);
	int C = CrossProuct(p3v, p3p1);
	if ((A>=0 & B>=0 &C>=0 ) || (A <= 0 & B <= 0 &  C<= 0))
	{
		return true;
	}
	return false;
	
}
bool CTriangle::IsValid(Point P1, Point  P2, Point P3) 
{
	if (P1.y > UI.ToolBarHeight && P2.y > UI.ToolBarHeight && P3.y > UI.ToolBarHeight&& P1.y < (UI.height - UI.StatusBarHeight) && P2.y < (UI.height - UI.StatusBarHeight) && P1.y < (UI.height - UI.StatusBarHeight))
	{
		return true;
	}
	return false;
}

CTriangle::~CTriangle()
{
}

void CTriangle::Save(ofstream &OutFile)
{

}
