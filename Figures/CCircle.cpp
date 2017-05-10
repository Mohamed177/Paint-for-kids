#include "CCircle.h"
#include <cmath>
CCircle::CCircle(Point P1, double R, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Raduis = R;

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
	OutFile<< "Circle" << ID << ' ' << Center.x << ' ' << Center.y << ' ' << Raduis << ' ';
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

void CCircle::Resize(float K = 2,bool zoom = false)
{
	double Raduis2 = K * Raduis;
	if (zoom)
		Raduis = Raduis2;
	else 
		if ((Center.y - Raduis2) >= UI.ToolBarHeight   && Center.y>UI.ToolBarHeight && Center.y<(UI.height - UI.StatusBarHeight) && (UI.height - UI.StatusBarHeight)>(Center.y + Raduis2))
		{
			Raduis = Raduis2;
		}
	return;

}
 Point CCircle::GetCenter() 
{
	 return Center;
}
 bool  CCircle::ValidMove(Point p ) 
 {
	 Point v1, v2;
	 v1.x = Center.x + p.x;
	 v1.y = Center.y + p.y;
	 if ((v1.y > UI.ToolBarHeight && (v1.y+Raduis) > UI.ToolBarHeight && (v1.y+Raduis) < (UI.height - UI.StatusBarHeight) && v1.x <= UI.width &&(v1.x-Raduis) <= UI.width && ( v1.x +Raduis)<=UI.width &&v1.x >=0 && (v1.x - Raduis) >=0 && (v1.x + Raduis) >=0))
	 {
		 return true;
	 }
	 return false;
 }

 void CCircle::Move(Point p)
 {
	 Center.x += p.x;
	 Center.y +=  p.y;
 }

 CFigure * CCircle:: copy() 
 {
	 CCircle *C = new CCircle(Center, Raduis, FigGfxInfo);
	 CFigure * v = C;
	 return v;
 }

 void CCircle::Zoom(float factor)
 {
	 Point wcenter, p;
	 wcenter.x = UI.width / 2;
	 wcenter.y = UI.height / 2;
	 if (factor > 1)
	 {
		 p.x = Center.x - wcenter.x;
		 p.y = Center.y - wcenter.y;
		 p.x *= factor-1;
		 p.y *= factor-1;
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

void CCircle::Load(ifstream &Infile) 
{
}
