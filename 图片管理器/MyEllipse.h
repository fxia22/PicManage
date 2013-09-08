#pragma once
#include "myline.h"
class MyEllipse :
	public MyLine
{
public:
	MyEllipse(void);
	MyEllipse(int,int,int,int,int,int,COLORREF);
	MyEllipse(MyLine&);
	virtual ~MyEllipse(void);
	void virtual draw(CDC& dc)const;
	bool isLine()const;
};

