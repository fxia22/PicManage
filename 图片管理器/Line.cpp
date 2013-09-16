
#include "StdAfx.h"
#include "Line.h"


Line::Line(void)
{
}

Line::Line(int a,int b,int c,int d):x1(a),y1(b),x2(c),y2(d),m_lineclr(RGB(255,255,0))
{
}

Line::Line(int a,int b,int c,int d,CString str):x1(a),y1(b),x2(c),y2(d),m_lineclr(RGB(255,255,0)),MyObject(str)
{
}



Line::~Line(void)
{
}

void Line::draw(CDC& dc)const
{
	//CPen pen(m_linestyle, m_linewidth, m_lineclr); 
	//CPen* pOldpen = dc.SelectObject(&pen);
	if (!isPoint())
	{
		dc.MoveTo(x1,y1);
		dc.LineTo(x2,y2);
	}
	//pen.DeleteObject();
	
}

bool Line::isPoint()const
{
	return ((x1==x2)&&(y1==y2));
}
