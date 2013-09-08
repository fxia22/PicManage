#pragma once
#include "MyObject.h"
class Line:public MyObject
{
public:
	
	int x1,y1,x2,y2;
	int m_linewidth;
	int m_linestyle;
	COLORREF m_lineclr;
	Line(void);
	Line(int,int,int,int);
	~Line(void);
	void draw(CDC& dc)const;
	bool isPoint()const;
};

