#include "stdafx.h"
#include "MyEllipse.h"


MyEllipse::MyEllipse(void):MyLine()
{
}

MyEllipse::MyEllipse(int x1,int y1,int x2,int y2,int style,int width,COLORREF clr):MyLine(x1,y1,x2,y2,style,width,clr)
{
}

MyEllipse::MyEllipse(MyLine& L):MyLine(L)
{
}

MyEllipse::~MyEllipse(void)
{
}

bool MyEllipse::isLine()const
{
	return ((_x1==_x2) ||(_y1 == _y2));
}

void  MyEllipse::draw(CDC& dc)const
{
	if (enable)
	if (isLine())
	{
		this->MyLine::draw(dc);
		return ;
	}
	else
	{
		CPen pen(m_style,m_width,m_clr); 
		CPen *penOld = dc.SelectObject( &pen ); 
		dc.SelectStockObject(NULL_BRUSH);   
		dc.Ellipse(_x1,_y1,_x2,_y2);

		dc.SelectObject(penOld);
		pen.DeleteObject();
	}
}