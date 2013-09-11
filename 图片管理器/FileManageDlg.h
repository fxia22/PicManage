#pragma once
#include "afxwin.h"
#include "Adomdb.h"

// CFileManageDlg 对话框

class CFileManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileManageDlg)

public:
	CFileManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileManageDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_FILEMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_VisibleFile;
	CListBox m_Group;
	CListBox m_FileInGroup;
	CEdit m_Groupname;
	afx_msg void OnBnClickedButtonAddgroup();
	Adomdb fileado;
	virtual BOOL OnInitDialog();
	CString  m_currentuser;
	afx_msg void OnBnClickedButtonAddToGroup();
	CString currentfile;
	CString currentsudo;
	CString currentgroup;
	afx_msg void OnLbnSelchangeListVisiblefile();
	afx_msg void OnLbnSelchangeListFilegroup();
};
