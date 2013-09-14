#include "stdafx.h"
#include "MyPolyLine.h"
using namespace std;

MyPolyLine::MyPolyLine(void):data()
{
}


MyPolyLine::~MyPolyLine(void)
{
}

void MyPolyLine::draw(CDC& dc)const
{
	
	for (int i=0;i<data.size();i++)
	{
		this->data[i]->draw(dc);
	}

}

void MyPolyLine::add(MyLine* obj)
{
	data.push_back(obj);
}

void MyPolyLine::moveto(int x, int y)
{
	_x1+=x;
	_y1+=y;
	_x2+=x;
	_y2+=y;
}
