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

	void OnBnClickedRadio(UINT ID);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio3();
};
