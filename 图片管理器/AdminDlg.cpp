// AdminDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "图片管理器.h"
#include "AdminDlg.h"
#include "afxdialogex.h"
using namespace std;

// CAdminDlg 对话框

IMPLEMENT_DYNAMIC(CAdminDlg, CDialogEx)

CAdminDlg::CAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdminDlg::IDD, pParent)
{

	m_username = _T("");
	m_sudo = _T("");
	m_pathname = _T("");
	m_current_operator = _T("");
}

CAdminDlg::~CAdminDlg()
{
}

void CAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST_USERSELECT, m_List_user);
	//  DDX_Control(pDX, IDC_LIST_SUDOCTRL, m_List_sudo);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_filepath);
	DDX_Control(pDX, IDC_LIST_TEST, m_List_sudo2);
	DDX_Control(pDX, IDC_LIST_USER2, m_List_user2);
}


BEGIN_MESSAGE_MAP(CAdminDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CAdminDlg::OnBnClickedButtonOpenFile)
	ON_LBN_SELCHANGE(IDC_LIST_TEST, &CAdminDlg::OnLbnSelchangeListTest)
	ON_LBN_SELCHANGE(IDC_LIST_USER2, &CAdminDlg::OnLbnSelchangeListUser2)
	ON_BN_CLICKED(IDOK, &CAdminDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAdminDlg 消息处理程序


void CAdminDlg::OnBnClickedButtonOpenFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"bmp格式 (*.bmp)|*.bmp||",NULL);
	if (fdlg.DoModal()==IDOK)
	{
		m_pathname = fdlg.GetPathName();
		GetDlgItem(IDC_EDIT_FILEPATH)->SetWindowText(m_pathname);
	}
}


BOOL CAdminDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	  m_List_sudo2.AddString("写权限");
	  m_List_sudo2.AddString("读权限");
	  m_sudo = "";
	// TODO:  在此添加额外的初始化
	  adminado.OnInitADOConn("用户");
	  adminado.m_pRecordset->MoveFirst();
	  while (!adminado.m_pRecordset->adoEOF)
	  {
		CString temp = (_bstr_t)(adminado.m_pRecordset->GetCollect("用户名"));
		//userlist.push_back(temp);
		m_List_user2.AddString(temp);
		adminado.m_pRecordset->MoveNext();
	  }
	  adminado.m_pRecordset->MoveFirst();
	  adminado.ExitConnect();

	  m_current_operator  = ((C图片管理器App*)AfxGetApp())->CurrentUser;





	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAdminDlg::OnLbnSelchangeListTest()
{
		
	if (m_List_sudo2.GetCurSel()==0) m_sudo= "读";
	else if (m_List_sudo2.GetCurSel()==1) m_sudo = "写";
}


void CAdminDlg::OnLbnSelchangeListUser2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_List_user2.GetText(m_List_user2.GetCurSel(),m_username);
	
}


void CAdminDlg::OnBnClickedOk()
{
	int state;
	// TODO: 在此添加控件通知处理程序代码
	if (m_pathname=="") 
	{
		AfxMessageBox("请选择文件");
		return;
	}

	if (m_sudo=="") 
	{
		AfxMessageBox("请选择权限");
		return;
	}
	if (m_username=="") 
	{
		AfxMessageBox("请选择用户");
		return;
	}
	state = adminado.CheckFileState(m_current_operator,m_pathname);
	
	if (state!=Adomdb::CAN_WRITE)
	{
		AfxMessageBox("您对于该文件没有写权限");
		return;
	}
	if (m_current_operator==m_username)
	{
		AfxMessageBox("您不能给自己授权");
		return;
	}
	adminado.OnInitADOConn("权限");
	adminado.NewFile(m_username,m_pathname,m_sudo);
	adminado.ExitConnect();
	AfxMessageBox("授权成功");
	return;
	CDialogEx::OnOK();
}
