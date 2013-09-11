#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
using namespace std;

// CAdminDlg �Ի���

class CAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminDlg)

public:
	CAdminDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdminDlg();

// �Ի�������
	enum { IDD = IDD_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl m_List_user;
//	CListCtrl m_List_sudo;
	CEdit m_filepath;
	afx_msg void OnBnClickedButtonOpenFile();
	virtual BOOL OnInitDialog();
	CListBox m_List_sudo2;
	CListBox m_List_user2;
	afx_msg void OnLbnSelchangeListTest();
	Adomdb adminado;
	CString m_username;
	CString m_sudo;
	CString m_pathname;
//	vector<CString> userlist;
	afx_msg void OnLbnSelchangeListUser2();
	afx_msg void OnBnClickedOk();
	CString m_current_operator;
};
