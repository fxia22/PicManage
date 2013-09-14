#include "stdafx.h"
#include "MyBezier.h"


MyBezier::MyBezier(void)
{
}


MyBezier::~MyBezier(void)
{
}

MyBezier::MyBezier(int x1,int y1,int x2,int y2,int style,int width,COLORREF clr):MyLine(x1,y2,x2,y2,style,width,clr)
{
	label  = "Bezier";
}

void MyBezier::draw(CDC& dc)const
{
	if(enable)
	{

	
		if (comp)
		{
			if (isPoint())
			{
				MyPoint p;
				p.draw(dc);
				return;
			}
			CPen pen(m_style,m_width,m_clr); 
			CPen *penOld = dc.SelectObject( &pen ); 
			POINT tempp[4];
			tempp[0].x = _x1;
			tempp[0].y = _y1;
			tempp[1].x = _x3;
			tempp[1].y = _y3;
			tempp[2].x = _x4;
			tempp[2].y = _y4;
			tempp[3].x = _x2;
			tempp[3].y = _y2;
			PolyBezier(dc,tempp,4);
			dc.SelectObject(penOld);
			pen.DeleteObject();
		}
		else
		{
			if (isPoint())
			{
				MyPoint p;
				p.draw(dc);
				return;
			}
			CPen pen(m_style,m_width,m_clr); 
			CPen *penOld = dc.SelectObject( &pen ); 

			dc.MoveTo(_x1,_y1);
			dc.LineTo(_x2,_y2);

			dc.SelectObject(penOld);
			pen.DeleteObject();
		}
	}

}

void MyBezier::moveto(int x, int y)
{
	_x1+=x;
	_x2+=x;
	_x3+=x;
	_x4+=x;
	_y1+=y;
	_y2+=y;
	_y3+=y;
	_y4+=y;

}
