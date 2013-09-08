#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CStyleDlg �Ի���

class CStyleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStyleDlg)

public:
	CStyleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStyleDlg();

// �Ի�������
	enum { IDD = IDD_STYLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawStSlider(NMHDR *pNMHDR, LRESULT *pResult);

public:
	 


	CSliderCtrl m_csc;
	CEdit m_linewidth;
	int m_width;
	int m_style;
	void OnBnClickedRadio(UINT ID);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnPaint();
//	afx_msg void OnTRBNThumbPosChangingStSlider(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
};
