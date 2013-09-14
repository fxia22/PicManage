#pragma once
class MyObject
{
public:
	CString label;
	MyObject(void):enable(true),selected(false)
	{
		label = "";
	}

	MyObject(CString str):enable(true),label(str),selected(false)
	{
		
	}



	virtual ~MyObject(void)
	{
	}

	virtual void draw(CDC& dc)const =0;
	virtual void moveto(int x,int y) = 0;
	bool enable;
	bool selected;
};

