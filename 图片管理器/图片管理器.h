
// ͼƬ������.h : ͼƬ������ Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "Adomdb.h"

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
	afx_msg void OnCreateele();
	afx_msg void OnCreateobj();
	afx_msg void OnCalladmin();
	
//	afx_msg void OnFileNew();
	afx_msg void OnFileNew();
public://�Լ�����ı���
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

extern CͼƬ������App theApp;
