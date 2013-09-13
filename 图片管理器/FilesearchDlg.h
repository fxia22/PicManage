#pragma once
#include "afxwin.h"


// CFilesearchDlg 对话框

class CFilesearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilesearchDlg)

public:
	CFilesearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFilesearchDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_FILESEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_keyword;
	CListBox m_file;
	Adomdb searchado;
	afx_msg void OnBnClickedButtonStartsearch();
	afx_msg void OnLbnDblclkList1Search();
};
