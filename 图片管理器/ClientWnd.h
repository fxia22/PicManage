#pragma once
#include "afxwin.h"
class CClientWnd :
	public CWnd
{
public:
	CClientWnd(void);
	virtual ~CClientWnd(void);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	WNDPROC* GetSuperWndProcAddr();
};

