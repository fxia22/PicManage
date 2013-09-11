
// 图片管理器.h : 图片管理器 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "Adomdb.h"

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
	afx_msg void OnCreateele();
	afx_msg void OnCreateobj();
	afx_msg void OnCalladmin();
	
//	afx_msg void OnFileNew();
	afx_msg void OnFileNew();
public://自己定义的变量
	CString CurrentUser;
	Adomdb ado;
	bool m_LoginStatus;
	afx_msg void OnUpdateFileNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
//	afx_msg void OnFileOpen();
	afx_msg void OnFileOpen();
//	bool firstdoc;
//	void NewFile(void);
	//afx_msg void OnMyFileOpen();
	Adomdb appado;
	afx_msg void OnUpdateMyfile(CCmdUI *pCmdUI);
	afx_msg void OnMyfile();
	afx_msg void OnUpdateLogin(CCmdUI *pCmdUI);
	afx_msg void OnMenuFileman();
	afx_msg void OnUpdateMenuFileman(CCmdUI *pCmdUI);
};

extern C图片管理器App theApp;
