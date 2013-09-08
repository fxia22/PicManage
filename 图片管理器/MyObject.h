#pragma once
class MyObject
{
public:

	MyObject(void)
	{
	}

	virtual ~MyObject(void)
	{
	}

	virtual void draw(CDC& dc)const =0;


};

