
// ͼƬ������.h : ͼƬ������ Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CͼƬ������App:
// �йش����ʵ�֣������ ͼƬ������.cpp
//

class CͼƬ������App : public CWinApp
{
public:
	CͼƬ������App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	afx_msg void OnLogout();
	afx_msg void OnLogin();
	DECLARE_MESSAGE_MAP()
};

extern CͼƬ������App theApp;
