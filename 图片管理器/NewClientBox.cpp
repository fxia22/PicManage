// NewClientBox.cpp : 实现文件
//
/************************************************************************/
/* 新用户对话框
Edited by xf
*/
/************************************************************************/
#include "stdafx.h"
#include "图片管理器.h"
#include "NewClientBox.h"
#include "afxdialogex.h"
#include "LogInBox.h"

// NewClientBox 对话框

IMPLEMENT_DYNAMIC(NewClientBox, CDialogEx)

NewClientBox::NewClientBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewClientBox::IDD, pParent)
{

	m_user = _T("");
	m_pass = _T("");
}

NewClientBox::~NewClientBox()
{
}

void NewClientBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USERNAME, username);
	DDX_Control(pDX, IDC_EDIT_PASS1, password1);
	DDX_Control(pDX, IDC_EDIT_PASS2, password2);
}


BEGIN_MESSAGE_MAP(NewClientBox, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewClientBox::OnBnClickedOk)
END_MESSAGE_MAP()


// NewClientBox 消息处理程序

/************************************************************************/
/* 点击ok                                                               */
/************************************************************************/
void NewClientBox::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_PASS1)->GetWindowText(m_pass);
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(m_user);//获得用户名、密码
	CString pass;
	GetDlgItem(IDC_EDIT_PASS2)->GetWindowText(pass);//获得第二次密码
	if ((m_user=="")||(m_pass=="")) 
	{
		AfxMessageBox("用户名或密码不能为空");
		return ;
	}
	if (m_pass.Compare(pass)!=0) 
		{AfxMessageBox("两次输入密码不一致");
		return ;
	}
	LogInBox* pd = (LogInBox*)GetParent();
	if (pd->CheckState(m_user,m_pass)!=LogInBox::NO_USER)
		{
			AfxMessageBox("用户名存在");
			return;
	}
	CDialogEx::OnOK();
}
