/************************************************************************/
/* 点类的实现
Edited by xf
*/
/************************************************************************/
#include "stdafx.h"
#include "MyPoint.h"


MyPoint::MyPoint(void):_x(0),_y(0),m_clr(RGB(0,0,0))
{
}

MyPoint::MyPoint(int x,int y,COLORREF clr):_x(x),_y(y),m_clr(clr)
{
	label = "point";
}

MyPoint::MyPoint(MyPoint& p)
{
	_x = p._x;
	_y = p._y;
	m_clr = p.m_clr;
}

MyPoint::~MyPoint(void)
{
}

void MyPoint::draw(CDC& dc)const
{
	dc.SetPixel(_x,_y,m_clr);
}

void MyPoint::moveto(int x, int y)
{
	_x+=x;
	_y+=y;
}
