#pragma once
#include "afxwin.h"


// CSizeDlg 对话框

class CSizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSizeDlg)

public:
	CSizeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSizeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1_SIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_height;
	CEdit m_width;
	afx_msg void OnBnClickedOk();
	int width;
	int height;
};
