#include "stdafx.h"
#include "MyMultipleLine.h"


MyMultipleLine::MyMultipleLine(void)
{
}


MyMultipleLine::MyMultipleLine(int x1,int y1,int x2,int y2,int style,int width,COLORREF clr):MyLine(x1,y1,x2,y2,style,width,clr)
{
	label = "MyMultipleLine";
}

void MyMultipleLine::AddPoint(int tx,int ty)
{
	data.push_back(MyPoint(tx-_x1,ty-_y1));
	_y2 = ty;
	_x2 = tx;
}

 MyMultipleLine::~MyMultipleLine(void)
{
	data.clear();
}


 void  MyMultipleLine::draw(CDC& dc)const
 {
	if (enable)
		{
		 CPen pen(m_style,m_width,m_clr); 
		 CPen *penOld = dc.SelectObject( &pen ); 
		 dc.SelectStockObject(NULL_BRUSH);   
		 if (data.size()>0)
		 {
			 dc.MoveTo(_x1,_y1);
			 dc.LineTo(_x1+data[0]._x,_y1+data[0]._y);
		 }
		 for (int i=1;i<data.size();i++)
		 {  
			 dc.MoveTo(_x1+data[i-1]._x,_y1+data[i-1]._y);
			 dc.LineTo(_x1+data[i]._x,_y1+data[i]._y);
		 }  

		 dc.SelectObject(penOld);
		 pen.DeleteObject();
	}
 }

 void MyMultipleLine::moveto(int x, int y)
 {
	 _x1+=x;
	 _x2+=x;
	 _y1+=y;
	 _y2+=y;
 }
