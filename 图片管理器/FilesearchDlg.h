#pragma once
#include "afxwin.h"


// CFilesearchDlg �Ի���

class CFilesearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilesearchDlg)

public:
	CFilesearchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFilesearchDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FILESEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_keyword;
	CListBox m_file;
	Adomdb searchado;
	afx_msg void OnBnClickedButtonStartsearch();
	afx_msg void OnLbnDblclkList1Search();
};
