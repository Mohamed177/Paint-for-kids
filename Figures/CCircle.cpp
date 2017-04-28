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
	double Raduis = ((P2.y - Center.y) *(P2.y - Center.y)) + ((P2.x - Center.x)*(P2.x - Center.x));
	double Raduis2 = ((P.y - Center.y) *(P.y - Center.y)) + ((P.x - Center.x)*(P.x - Center.x));
	if (Raduis2<=Raduis )
	{
		return true;
	}
	return false;
}

void CCircle::Save(ofstream & OutFile) 
{
	OutFile<< "Circle" << ID << ' ' << Center.x << ' ' << Center.y << ' ' << P2.x << ' ' << P2.y << ' ';
	OutFile<< FigGfxInfo.DrawClr;
	OutFile<< " ";
	if (FigGfxInfo.isFilled)
	{
		OutFile << FigGfxInfo.FillClr;
	}
	else
	{
		OutFile << "Not_Filled";
	}
	OutFile << endl;
}

void CCircle::Resize(float factor = 2)
{
	return;
}