#pragma once


// CommandDlg 对话框

class CommandDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CommandDlg)

public:
	CommandDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CommandDlg();

// 对话框数据
	enum { IDD = IDD_CMD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
