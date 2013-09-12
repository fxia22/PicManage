#pragma once
#include "myline.h"
class MyBezier :
	public MyLine
{
public:
	int _x3,_x4,_y3,_y4;
public:
	MyBezier(void);
	MyBezier(int,int,int,int,int,int,COLORREF);
	virtual ~MyBezier(void);
	void virtual draw(CDC& dc)const;
//	bool complete;
	bool comp;
};

