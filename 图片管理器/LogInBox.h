#pragma once


// LogInBox �Ի���

class LogInBox : public CDialogEx
{
	DECLARE_DYNAMIC(LogInBox)

public:
	LogInBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LogInBox();

// �Ի�������
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNewclient();
};
