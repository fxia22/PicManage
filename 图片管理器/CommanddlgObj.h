#pragma once


// CommandDlgObj �Ի���

class CommandDlgObj : public CDialogEx
{
	DECLARE_DYNAMIC(CommandDlgObj)

public:
	CommandDlgObj(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CommandDlgObj();

// �Ի�������
	enum { IDD = IDD_CMDDLGOBJ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
