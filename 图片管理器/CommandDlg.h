#pragma once


// CommandDlg �Ի���

class CommandDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CommandDlg)

public:
	CommandDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CommandDlg();

// �Ի�������
	enum { IDD = IDD_CMD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
