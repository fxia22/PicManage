#pragma once


// LogInBox �Ի���

class LogInBox : public CDialogEx
{
	DECLARE_DYNAMIC(LogInBox)
	enum {
		CHECK_OK=0,
		NO_USER,
		WRONG_PASSWORD
	};
public:
	LogInBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LogInBox();

// �Ի�������
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int CheckState(CString& name, CString& pass);
private:
	afx_msg void OnBnClickedNewclient();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
private:
	Adomdb ado;
};
