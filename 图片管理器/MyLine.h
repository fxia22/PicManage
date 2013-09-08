#pragma once
#include "myobject.h"
#include "MyPoint.h"
class MyLine :
	public MyObject
{
public:
	int _x1,_x2,_y1,_y2;
	int m_style;
	int m_width;
	COLORREF m_clr;
public:
	MyLine(void);    
	MyLine(MyPoint&,MyPoint&);
	MyLine(int,int,int,int,int,int,COLORREF);
	MyLine(MyLine&);
	virtual ~MyLine(void);
	void virtual draw(CDC& dc)const;
	bool isPoint()const;
};

