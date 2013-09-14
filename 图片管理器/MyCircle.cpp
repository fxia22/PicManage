#include "stdafx.h"
#include "MyCircle.h"


MyCircle::MyCircle(void):MyLine()
{
}

MyCircle::MyCircle(int x1,int y1,int x2,int y2,int style,int width,COLORREF clr):MyLine(x1,y1,x2,y2,style,width,clr)
{
	label = "Circle";
}

MyCircle::MyCircle(MyLine& L):MyLine(L)
{
}

MyCircle::~MyCircle(void)
{
}


void  MyCircle::draw(CDC& dc)const
{
	if (enable)
	if (isPoint())
	{
		return ;
	}
	else
	{
		CPen pen(m_style,m_width,m_clr); 
		CPen *penOld = dc.SelectObject( &pen ); 
		dc.SelectStockObject(NULL_BRUSH);   
		
		int r = (int)sqrt((_x1-_x2)*(_x1-_x2)+(_y1-_y2)*(_y1-_y2));
		dc.Ellipse(_x1-r,_y1-r,_x1+r,_y1+r);

		dc.SelectObject(penOld);
		pen.DeleteObject();
	}
}

void MyCircle:: moveto(int x,int y)
{
	_x1+=x;
	_x2+=x;
	_y1+=y;
	_y2+=y;
}