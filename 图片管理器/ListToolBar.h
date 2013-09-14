#pragma once
#include "afxext.h"

class CListToolBar :
	public CToolBar
{
public:
	CListToolBar(void);
	virtual ~CListToolBar(void);
	DECLARE_MESSAGE_MAP()
public:
	CListBox Lis;
};

