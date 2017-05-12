#include "CCircle.h"
#include <cmath>
CCircle::CCircle(Point P1, double R, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Radius = R;

}
void CCircle::Draw(Output *pOut) const
{
	pOut->DrawCIRC(Center, Radius, FigGfxInfo, Selected);
}

bool CCircle::Is_Selected(Point P) const
{

	double Radius2 = sqrt(((P.y - Center.y) *(P.y - Center.y)) + ((P.x - Center.x)*(P.x - Center.x)));
	if (Radius2<=Radius )
	{
		return true;
	}
	return false;
}

void CCircle::Save(ofstream & OutFile) 
{
	OutFile << "Circle " << ID << ' ' << Center.x << ' ' << Center.y << ' ' << Radius << ' ' << FigGfxInfo.BorderWdth << ' ';
	OutFile<< (string)FigGfxInfo.DrawClr;
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
	double Radius2 = K * Radius;
	if (zoom)
		Radius = Radius2;
	else 
		if ((Center.y - Radius2) >= UI.ToolBarHeight   && Center.y>UI.ToolBarHeight && Center.y<(UI.height - UI.StatusBarHeight) && (UI.height - UI.StatusBarHeight)>(Center.y + Radius2))
		{
			Radius = Radius2;
		}
	return;

}
 Point CCircle::GetCenter() 
{
	 return Center;
}
 bool  CCircle::ValidMove(Point p, bool scramble = 0)
 {
	 Point v1, v2;
	 v1.x = Center.x + p.x;
	 v1.y = Center.y + p.y;
	 int left_border = 0;
	 if (scramble)
		 left_border = UI.width / 2;
	 if ((v1.y > UI.ToolBarHeight && (v1.y+Radius) > UI.ToolBarHeight && (v1.y+Radius) < (UI.height - UI.StatusBarHeight) && v1.x <= UI.width &&(v1.x-Radius) <= UI.width && ( v1.x +Radius)<=UI.width &&v1.x >=left_border && (v1.x - Radius) >=left_border && (v1.x + Radius) >= left_border))
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
	 CCircle *C = new CCircle(Center, Radius, FigGfxInfo);
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

 void CCircle::PrintInfo(Output * pOut)
 {
	 string info = "Cicle of ID : " + to_string(ID) + " Center : ( " + to_string(Center.x) + " , " + to_string(Center.y);
	 info += " ) Radius : " + to_string(Radius) + ' ';
	 string Color = FigGfxInfo.DrawClr;
	 Color += ' ';
	 if (FigGfxInfo.isFilled)
		 Color += FigGfxInfo.FillClr;
	 else 
		 Color += " No Fill.";
	 info += Color;
	 pOut->PrintMessage(info);
 }

void CCircle::Load(ifstream &Infile) 
{
	string drwColor, Fcolor;
	Infile >> ID >> Center.x >> Center.y >> Radius >> FigGfxInfo.BorderWdth >> drwColor >> Fcolor;
	FigGfxInfo.DrawClr = drwColor;
}


char CCircle::GetType()
{
	return 'C';
}