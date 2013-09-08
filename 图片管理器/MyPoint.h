#pragma once
#include "myobject.h"
class MyPoint :
	public MyObject
{
public:
	int _x,
		_y;
	COLORREF m_clr;
public:
	MyPoint(void);
	MyPoint(int,int,COLORREF clr=RGB(0,0,0));
	MyPoint(MyPoint&);
	virtual ~MyPoint(void);
	virtual void draw(CDC& dc)const;
	
};

