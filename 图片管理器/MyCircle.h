#pragma once
#include "myline.h"
#include "cmath"
class MyCircle :
	public MyLine
{
public:
	MyCircle(void);
	MyCircle(int,int,int,int,int,int,COLORREF);
	MyCircle(MyLine&);
	virtual ~MyCircle(void);
	void virtual draw(CDC& dc)const;
};

