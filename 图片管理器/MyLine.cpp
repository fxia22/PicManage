#include "stdafx.h"
#include "MyLine.h"


MyLine::MyLine(void):_x1(0),_x2(0),_y1(0),_y2(0),m_width(1),m_style(PS_SOLID),m_clr(RGB(0,0,0))
{
}


MyLine::MyLine(int x1,int y1,int x2,int y2,int style,int width ,COLORREF clr):_x1(x1),_y1(y1),_x2(x2),_y2(y2),m_style(style),m_width(width),m_clr(clr),MyObject("Line")
{
}


MyLine::MyLine(int x1,int y1,int x2,int y2,int style,int width ,COLORREF clr,CString str):_x1(x1),_y1(y1),_x2(x2),_y2(y2),m_style(style),m_width(width),m_clr(clr),MyObject(str)
{
}

MyLine::MyLine(MyPoint& p1,MyPoint& p2):_x1(p1._x),_y1(p1._y),_x2(p2._x),_y2(p2._y),m_clr(p1.m_clr),m_style(PS_SOLID),m_width(1)
{
}


MyLine::MyLine(MyLine& L):_x1(L._x1),_x2(L._x2),_y1(L._y1),_y2(L._y2),m_clr(L.m_clr),m_style(L.m_style),m_width(L.m_width)
{
}

void MyLine::draw(CDC& dc)const
{
	if (enable)
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

bool MyLine::isPoint()const
{
	return ((_x1==_x2)&&(_y1==_y2));
}



MyLine::~MyLine(void)
{
}

void MyLine::moveto(int x,int y)
{
	_x1+=x;
	_x2+=x;
	_y1+=y;
	_y2+=y;
}