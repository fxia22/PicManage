#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CStyleDlg 对话框

class CStyleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStyleDlg)

public:
	CStyleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStyleDlg();

// 对话框数据
	enum { IDD = IDD_STYLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawStSlider(NMHDR *pNMHDR, LRESULT *pResult);

public:
	 


	CSliderCtrl m_csc;
	CEdit m_linewidth;

	void OnBnClickedRadio(UINT ID);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio3();
};
