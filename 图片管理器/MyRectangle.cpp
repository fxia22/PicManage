/************************************************************************/
/* 矩形类的实现
Edited by xf
*/
/************************************************************************/
#include "stdafx.h"
#include "MyRectangle.h"


MyRectangle::MyRectangle(void):MyLine()
{
}

MyRectangle::MyRectangle(int x1,int y1,int x2,int y2,int style,int width,COLORREF clr):MyLine(x1,y1,x2,y2,style,width,clr)
{
	label = "Rectangle";
}

MyRectangle::MyRectangle(MyLine& L):MyLine(L)
{
}

MyRectangle::~MyRectangle(void)
{
}

bool MyRectangle::isLine()const
{
	return ((_x1==_x2) ||(_y1 == _y2));
}

void  MyRectangle::draw(CDC& dc)const
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
		dc.Rectangle(_x1,_y1,_x2,_y2);

		dc.SelectObject(penOld);
		pen.DeleteObject();
	}
}

bool MyRectangle::includeLine( MyLine* L)
{
	
	
	int minx = min(_x1,_x2);
	int maxx = max(_x1,_x2);
	int miny = min(_y1,_y2);
	int maxy = max(_y1,_y2);

	if ((L->_x1>minx)&&(L->_x1<maxx)&&(L->_x2>minx)&&(L->_x2<maxx)&&(L->_y1>miny)&&(L->_y1<maxy)&&(L->_y2>miny)&&(L->_y2<maxy))
		return true;
	return false;
}


void MyRectangle::moveto(int x, int y)
{
	_x1+=x;
	_x2+=x;
	_y1+=y;
	_y2+=y;
}
