#pragma once
#include "afxwin.h"


// CSizeDlg �Ի���

class CSizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSizeDlg)

public:
	CSizeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSizeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1_SIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_height;
	CEdit m_width;
	afx_msg void OnBnClickedOk();
	int width;
	int height;
};
