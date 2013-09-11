// FileManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "FileManageDlg.h"
#include "afxdialogex.h"


// CFileManageDlg �Ի���

IMPLEMENT_DYNAMIC(CFileManageDlg, CDialogEx)

CFileManageDlg::CFileManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileManageDlg::IDD, pParent)
{

	m_currentuser = _T("");
}

CFileManageDlg::~CFileManageDlg()
{
}

void CFileManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VISIBLEFILE, m_VisibleFile);
	DDX_Control(pDX, IDC_LIST_FILEGROUP, m_Group);
	DDX_Control(pDX, IDC_LIST_FILE_IN_GROUP, m_FileInGroup);
	DDX_Control(pDX, IDC_EDIT_ADDGROUP, m_Groupname);
}


BEGIN_MESSAGE_MAP(CFileManageDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDGROUP, &CFileManageDlg::OnBnClickedButtonAddgroup)
END_MESSAGE_MAP()


// CFileManageDlg ��Ϣ�������


void CFileManageDlg::OnBnClickedButtonAddgroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_Groupname.GetWindowTextA(str);
	if (str!="")
	{
		m_Groupname.SetWindowText("");
		m_Group.AddString(str);
	}
}



BOOL CFileManageDlg::OnInitDialog()
{
	CString du = "��";
	CDialogEx::OnInitDialog();
	m_currentuser = ((CͼƬ������App*)AfxGetApp())->CurrentUser;
	fileado.OnInitADOConn("Ȩ��");
	fileado.m_pRecordset->MoveFirst();
	while (!fileado.m_pRecordset->adoEOF)
	{
		if (m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("�û���")))==0)
		{
			CString name = (_bstr_t)(fileado.m_pRecordset->GetCollect("�ļ�·��"));
			if (du.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("����Ȩ��")))==0)
				name+="(ֻ��)";
			m_VisibleFile.AddString(name);
		}
		fileado.m_pRecordset->MoveNext();
	}
	fileado.m_pRecordset->MoveFirst();
	fileado.ExitConnect();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
