// FileManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "图片管理器.h"
#include "FileManageDlg.h"
#include "afxdialogex.h"


// CFileManageDlg 对话框

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


// CFileManageDlg 消息处理程序


void CFileManageDlg::OnBnClickedButtonAddgroup()
{
	// TODO: 在此添加控件通知处理程序代码
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
	CString du = "读";
	CDialogEx::OnInitDialog();
	m_currentuser = ((C图片管理器App*)AfxGetApp())->CurrentUser;
	fileado.OnInitADOConn("权限");
	fileado.m_pRecordset->MoveFirst();
	while (!fileado.m_pRecordset->adoEOF)
	{
		if (m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("用户名")))==0)
		{
			CString name = (_bstr_t)(fileado.m_pRecordset->GetCollect("文件路径"));
			if (du.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("访问权限")))==0)
				name+="(只读)";
			m_VisibleFile.AddString(name);
		}
		fileado.m_pRecordset->MoveNext();
	}
	fileado.m_pRecordset->MoveFirst();
	fileado.ExitConnect();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
