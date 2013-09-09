#pragma once
class MyObject
{
public:

	MyObject(void):enable(true)
	{
	}

	virtual ~MyObject(void)
	{
	}

	virtual void draw(CDC& dc)const =0;

	bool enable;
};

