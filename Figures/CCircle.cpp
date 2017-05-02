#include "CCircle.h"

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Raduis = sqrt(((P2.y - Center.y) *(P2.y - Center.y)) + ((P2.x - Center.x)*(P2.x - Center.x)));
	this->P2 = P2;

}
void CCircle::Draw(Output *pOut) const
{
	pOut->DrawCIRC(Center, Raduis, FigGfxInfo, Selected);
}

bool CCircle::Is_Selected(Point P) const
{

	double Raduis2 = sqrt(((P.y - Center.y) *(P.y - Center.y)) + ((P.x - Center.x)*(P.x - Center.x)));
	if (Raduis2<=Raduis )
	{
		return true;
	}
	return false;
}

void CCircle::Save(ofstream & OutFile) 
{
	OutFile<< "Circle" << ID << ' ' << Center.x << ' ' << Center.y << ' ' << P2.x << ' ' << P2.y << ' ';
	OutFile<< (string)FigGfxInfo.DrawClr;
	OutFile<< " ";
	if (FigGfxInfo.isFilled)
	{
		OutFile << ' ' << (string)FigGfxInfo.FillClr;
	}
	else
	{
		OutFile << " NO_FILL";
	}
	OutFile << endl;
}

void CCircle::Resize(float K = 2)
{
	double Raduis2 = K * Raduis;
	if ((Center.y - Raduis2) >= UI.ToolBarHeight   && Center.y>UI.ToolBarHeight && Center.y<(UI.height - UI.StatusBarHeight) && (UI.height - UI.StatusBarHeight)>(Center.y + Raduis2))
	{
		Raduis = Raduis2;
	}
	return;

}
void CCircle::Load(ifstream &Infile) 
{
}