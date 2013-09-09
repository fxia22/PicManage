#pragma once
#include "myobject.h"
#include "MyLine.h"
#include <vector>
using namespace std;

class MyPolyLine :
	public MyObject
{
public:
	vector<MyLine*> data;

public:

	MyPolyLine(void);
	virtual ~MyPolyLine(void);
	virtual void draw(CDC& dc)const;
	void add(MyLine* obj);
};

