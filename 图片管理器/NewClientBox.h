#pragma once
#include "afxwin.h"


// NewClientBox �Ի���

class NewClientBox : public CDialogEx
{
	DECLARE_DYNAMIC(NewClientBox)

public:
	NewClientBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NewClientBox();

// �Ի�������
	enum { IDD = IDD_NEWCLIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit username;
	CEdit password1;
	CEdit password2;
	CString m_user;
	CString m_pass;
};
