#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
using namespace std;

// CAdminDlg 对话框

class CAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminDlg)

public:
	CAdminDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdminDlg();

// 对话框数据
	enum { IDD = IDD_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	private:
//	CListCtrl m_List_user;
//	CListCtrl m_List_sudo;
	CEdit m_filepath;
	afx_msg void OnBnClickedButtonOpenFile();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeListTest();
	afx_msg void OnLbnSelchangeListUser2();
	afx_msg void OnBnClickedOk();
private:
	CListBox m_List_sudo2;
	CListBox m_List_user2;
	
	Adomdb adminado;
	CString m_username;
	CString m_sudo;
	CString m_pathname;
//	vector<CString> userlist;
	
	CString m_current_operator;
};
