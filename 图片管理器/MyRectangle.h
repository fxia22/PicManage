#pragma once
#include "myline.h"
class MyRectangle :
	public MyLine
{
public:
	MyRectangle(void);
	MyRectangle(int,int,int,int,int,int,COLORREF);
	MyRectangle(MyLine&);
	virtual ~MyRectangle(void);
	void virtual draw(CDC& dc)const;
	bool isLine()const;
	bool includeLine( MyLine* L);
};

