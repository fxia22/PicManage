#pragma once
#include "afxwin.h"


// NewClientBox 对话框

class NewClientBox : public CDialogEx
{
	DECLARE_DYNAMIC(NewClientBox)

public:
	NewClientBox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~NewClientBox();

// 对话框数据
	enum { IDD = IDD_NEWCLIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnBnClickedOk();
	CEdit username;
	CEdit password1;
	CEdit password2;
public:
	CString m_user;
	CString m_pass;
};
