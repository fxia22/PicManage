#pragma once


// LogInBox 对话框

class LogInBox : public CDialogEx
{
	DECLARE_DYNAMIC(LogInBox)
	enum {
		CHECK_OK=0,
		NO_USER,
		WRONG_PASSWORD
	};
public:
	LogInBox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LogInBox();

// 对话框数据
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNewclient();
	Adomdb ado;
	int CheckState(CString& name, CString& pass);
	afx_msg void OnBnClickedOk();
};
