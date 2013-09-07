#pragma once


// CAdminDlg 对话框

class CAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminDlg)

public:
	CAdminDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdminDlg();

// 对话框数据
	enum { IDD = IDD_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
