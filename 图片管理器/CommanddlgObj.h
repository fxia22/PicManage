#pragma once


// CommandDlgObj 对话框

class CommandDlgObj : public CDialogEx
{
	DECLARE_DYNAMIC(CommandDlgObj)

public:
	CommandDlgObj(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CommandDlgObj();

// 对话框数据
	enum { IDD = IDD_CMDDLGOBJ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
