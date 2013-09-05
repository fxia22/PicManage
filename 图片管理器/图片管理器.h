
// 图片管理器.h : 图片管理器 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// C图片管理器App:
// 有关此类的实现，请参阅 图片管理器.cpp
//

class C图片管理器App : public CWinApp
{
public:
	C图片管理器App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	afx_msg void OnLogout();
	afx_msg void OnLogin();
	DECLARE_MESSAGE_MAP()
};

extern C图片管理器App theApp;
