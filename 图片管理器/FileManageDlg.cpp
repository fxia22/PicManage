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
	currentfile = _T("");
	currentsudo = _T("");
	currentgroup = _T("");
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
	ON_BN_CLICKED(IDC_BUTTON_ADD_TO_GROUP, &CFileManageDlg::OnBnClickedButtonAddToGroup)
	ON_LBN_SELCHANGE(IDC_LIST_VISIBLEFILE, &CFileManageDlg::OnLbnSelchangeListVisiblefile)
	ON_LBN_SELCHANGE(IDC_LIST_FILEGROUP, &CFileManageDlg::OnLbnSelchangeListFilegroup)
	ON_LBN_DBLCLK(IDC_LIST_FILE_IN_GROUP, &CFileManageDlg::OnLbnDblclkListFileInGroup)
	ON_LBN_DBLCLK(IDC_LIST_VISIBLEFILE, &CFileManageDlg::OnLbnDblclkListVisiblefile)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEFILE, &CFileManageDlg::OnBnClickedButtonRemovefile)
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
			if (m_VisibleFile.FindString(-1,name)==-1)
			{m_VisibleFile.AddString(name);
			}
			
		}
		fileado.m_pRecordset->MoveNext();
	}
	fileado.m_pRecordset->MoveFirst();
	fileado.ExitConnect();


	fileado.OnInitADOConn("图片组");
	fileado.m_pRecordset->MoveFirst();
	while (!fileado.m_pRecordset->adoEOF)
	{
		if (m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("用户名")))==0)
		{
			CString group =  (_bstr_t)(fileado.m_pRecordset->GetCollect("图片组"));
			if (m_Group.FindString(-1,group)==-1)m_Group.AddString(group);
		}
		fileado.m_pRecordset->MoveNext();
	}
	fileado.m_pRecordset->MoveFirst();
	fileado.ExitConnect();





	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CFileManageDlg::OnBnClickedButtonAddToGroup()
{
	// TODO: 在此添加控件通知处理程序代码
	if ((currentfile=="")||(currentgroup==""))
	{
		AfxMessageBox("请选择项");
		return;
	}
	fileado.OnInitADOConn("图片组");
	fileado.NewFileToGroup(m_currentuser,currentfile,currentsudo,currentgroup);
	fileado.ExitConnect();

	fileado.OnInitADOConn("图片组");
	fileado.m_pRecordset->MoveFirst();
	while (!fileado.m_pRecordset->adoEOF)
	{
		if ((m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("用户名")))==0)&& (currentgroup.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("图片组")))==0))
		{
			CString name =  (_bstr_t)(fileado.m_pRecordset->GetCollect("文件路径"));
			if (m_FileInGroup.FindString(-1,name)==-1)
			{
				m_FileInGroup.AddString(name);
			}

		}
		fileado.m_pRecordset->MoveNext();
	}
	fileado.m_pRecordset->MoveFirst();
	fileado.ExitConnect();

	
}


void CFileManageDlg::OnLbnSelchangeListVisiblefile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_VisibleFile.GetText(m_VisibleFile.GetCurSel(),str);
	if (str.Find("只读")!=-1) 
		{currentsudo ="读";
		currentfile = str.Left(str.GetLength()-6);
	
	}
	else {
		currentsudo = "写";
		currentfile = str;
	}

}


void CFileManageDlg::OnLbnSelchangeListFilegroup()
{
	// TODO: 在此添加控件通知处理程序代码
	 m_Group.GetText(m_Group.GetCurSel(),currentgroup);
	 m_FileInGroup.ResetContent();
	 //AfxMessageBox(currentgroup);
	 fileado.OnInitADOConn("图片组");
	 fileado.m_pRecordset->MoveFirst();
	 while (!fileado.m_pRecordset->adoEOF)
	 {
		 if ((m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("用户名")))==0)&& (currentgroup.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("图片组")))==0))
		 {
			 CString name =  (_bstr_t)(fileado.m_pRecordset->GetCollect("文件路径"));
			if (m_FileInGroup.FindString(-1,name)==-1)
			{
					m_FileInGroup.AddString(name);
			}
		
		 }
		 fileado.m_pRecordset->MoveNext();
	 }
	 fileado.m_pRecordset->MoveFirst();
	 fileado.ExitConnect();
}



void CFileManageDlg::OnLbnDblclkListFileInGroup()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_FileInGroup.GetCurSel() == -1)
	{
		return;
	}
	CString str;
	m_FileInGroup.GetText(m_FileInGroup.GetCurSel(),str);
	((C图片管理器App*)AfxGetApp())->OnCerTainFileOpen(str);
	OnCancel();
}


void CFileManageDlg::OnLbnDblclkListVisiblefile()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_VisibleFile.GetCurSel() == -1)
	{
		return;
	}
	CString str;
	m_VisibleFile.GetText(m_VisibleFile.GetCurSel(),str);
	((C图片管理器App*)AfxGetApp())->OnCerTainFileOpen(str);
	OnCancel();


}


void CFileManageDlg::OnBnClickedButtonRemovefile()
{
	// TODO: 在此添加控件通知处理程序代码
	if (currentsudo =="读")
	{
		AfxMessageBox("您对该文件只有读权限，不能删除");
		return;
	}

	else
	{
		CFile::Remove(currentfile);
		fileado.OnInitADOConn("权限");
		fileado.m_pRecordset->MoveFirst();
		while (!fileado.m_pRecordset->adoEOF)
		{
			
				CString name =  (_bstr_t)(fileado.m_pRecordset->GetCollect("文件路径"));
				if (name==currentfile)
				{
					fileado.m_pRecordset->Delete(adAffectCurrent);
					fileado.m_pRecordset->Update();
					fileado.ExitConnect();
					break;
				}
				fileado.m_pRecordset->MoveNext();

			}
			
		AfxMessageBox("文件删除成功!");


		m_VisibleFile.ResetContent();
		CString du = "读";
		fileado.OnInitADOConn("权限");
		fileado.m_pRecordset->MoveFirst();
		while (!fileado.m_pRecordset->adoEOF)
		{
			if (m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("用户名")))==0)
			{
				CString name = (_bstr_t)(fileado.m_pRecordset->GetCollect("文件路径"));
				if (du.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("访问权限")))==0)
					name+="(只读)";
				if (m_VisibleFile.FindString(-1,name)==-1)
				{m_VisibleFile.AddString(name);
				}

			}
			fileado.m_pRecordset->MoveNext();
		}
		fileado.m_pRecordset->MoveFirst();
		fileado.ExitConnect();

	}







}
