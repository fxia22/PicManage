#pragma once
#include "myline.h"
#include "MyPoint.h"
#include <vector>
using namespace std;


class MyMultipleLine :
	public MyLine
{
public:
	MyMultipleLine(void);
	MyMultipleLine(int,int,int,int,int,int,COLORREF);
	virtual ~MyMultipleLine(void);
	void virtual draw(CDC& dc)const;
	void AddPoint(int,int);
private:
	vector<MyPoint> data;
	

public:
	virtual void moveto(int x, int y);
};

