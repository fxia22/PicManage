#pragma once
#include "afxwin.h"
#include "Adomdb.h"

// CFileManageDlg �Ի���

class CFileManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileManageDlg)

public:
	CFileManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileManageDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FILEMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	
	afx_msg void OnBnClickedButtonAddgroup();
	
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonAddToGroup();
	
	afx_msg void OnLbnSelchangeListVisiblefile();
	afx_msg void OnLbnSelchangeListFilegroup();
	afx_msg void OnLbnDblclkListFileInGroup();
	afx_msg void OnLbnDblclkListVisiblefile();
private:
	CString currentfile;
	CString currentsudo;
	CString currentgroup;
	CListBox m_VisibleFile;
	CListBox m_Group;
	CListBox m_FileInGroup;
	CEdit m_Groupname;
	Adomdb fileado;
	CString  m_currentuser;
public:
	afx_msg void OnBnClickedButtonRemovefile();
};
