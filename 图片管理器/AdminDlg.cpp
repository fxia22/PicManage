// AdminDlg.cpp : 实现文件
//
/************************************************************************/
/* 权限管理对话框的实现
Edited by xf
*/
/************************************************************************/
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

/************************************************************************/
/* 打开文件，将文件名载入到编辑框中
*/
/************************************************************************/
void CAdminDlg::OnBnClickedButtonOpenFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"bmp格式 (*.bmp)|*.bmp||",NULL);
	if (fdlg.DoModal()==IDOK)
	{
		m_pathname = fdlg.GetPathName();
		GetDlgItem(IDC_EDIT_FILEPATH)->SetWindowText(m_pathname);
	}
	CImage img;
	img.Load(m_pathname);
	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_STATIC_PICTURE2);
	CDC *pDC = pWnd->GetDC();
	pWnd->GetClientRect(&rect);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	img.Draw(pDC->m_hDC,rect);
	ReleaseDC( pDC );

}

/************************************************************************/
/* 
初始化对话框时，将当前用户可见文件载入listbox
*/
/************************************************************************/
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
		CString temp = (_bstr_t)(adminado.m_pRecordset->GetCollect("用户名"));//如果数据库中对应改用户有某文件，则该文件对该用户可见
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

/************************************************************************/
/* 
更改权限
*/
/************************************************************************/
void CAdminDlg::OnLbnSelchangeListTest()
{
		
	if (m_List_sudo2.GetCurSel()==0) m_sudo= "读";
	else if (m_List_sudo2.GetCurSel()==1) m_sudo = "写";
}

/************************************************************************/
/* 更改被选定用户                                                                     */
/************************************************************************/
void CAdminDlg::OnLbnSelchangeListUser2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_List_user2.GetText(m_List_user2.GetCurSel(),m_username);
	
}
/************************************************************************/
/* 
点击ok，判断是否可以授权，如果可以，则实现授权
*/
/************************************************************************/

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
	state = adminado.CheckFileState(m_current_operator,m_pathname);//直接调用了adomdb类的函数
	
	if (state!=Adomdb::CAN_WRITE)
	{
		AfxMessageBox("您对于该文件没有写权限");
		return;
	}
	if (m_current_operator==m_username)
	{
		AfxMessageBox("您不能给自己授权");//存在很多处理用户的错误输入
		return;
	}
	adminado.OnInitADOConn("权限");
	adminado.NewFile(m_username,m_pathname,m_sudo);
	adminado.ExitConnect();
	AfxMessageBox("授权成功");
	return;
	CDialogEx::OnOK();
}
