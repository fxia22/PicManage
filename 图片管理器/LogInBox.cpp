// LogInBox.cpp : 实现文件
//

#include "stdafx.h"
#include "图片管理器.h"
#include "LogInBox.h"
#include "afxdialogex.h"
#include "NewClientBox.h"


// LogInBox 对话框

IMPLEMENT_DYNAMIC(LogInBox, CDialogEx)

LogInBox::LogInBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(LogInBox::IDD, pParent)
{

}

LogInBox::~LogInBox()
{
}

void LogInBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LogInBox, CDialogEx)
	ON_BN_CLICKED(IDC_NEWCLIENT, &LogInBox::OnBnClickedNewclient)
	ON_BN_CLICKED(IDOK, &LogInBox::OnBnClickedOk)
END_MESSAGE_MAP()


// LogInBox 消息处理程序


void LogInBox::OnBnClickedNewclient()
{
	
	NewClientBox ncb;
	if (ncb.DoModal()==IDOK){
	
	ado.OnInitADOConn("用户");
	ado.NewUser(ncb.m_user,ncb.m_pass);
	ado.ExitConnect();
	
	
	}
	


	// TODO: 在此添加控件通知处理程序代码
}


int LogInBox::CheckState(CString& name, CString& pass)
{
		bool userexist = false;
		bool passwordright = false;
		ado.OnInitADOConn("用户");
		ado.m_pRecordset->MoveFirst();
		while (!ado.m_pRecordset->adoEOF)
		{
			if (name.Compare((_bstr_t)(ado.m_pRecordset->GetCollect("用户名")))==0)
			{
				userexist = true;
				if (pass.Compare((_bstr_t)(ado.m_pRecordset->GetCollect("密码")))==0)
				{
					passwordright = true;
					break;
				}
			}
			ado.m_pRecordset->MoveNext();
		}
		ado.m_pRecordset->MoveFirst();
	

		ado.ExitConnect();
	

	if (userexist)
		 if (passwordright) return CHECK_OK;
		 else return WRONG_PASSWORD;
	else
		return NO_USER;
	return 0;
}


void LogInBox::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString user;
	CString pass;
	GetDlgItem(IDC_EDIT_LOGINUSERNAME)->GetWindowText(user);
	GetDlgItem(IDC_EDIT_LOGINPASS)->GetWindowText(pass);
	if ((user=="")||(pass=="")) 
	{
		AfxMessageBox("用户名或密码不能为空");
		return ;
	}
	if (CheckState(user,pass)==WRONG_PASSWORD)
	{
		AfxMessageBox("密码错误");
		return ;
	}

	if (CheckState(user,pass)==NO_USER)
	{
		AfxMessageBox("用户不存在");
		return ;
	}
	if (CheckState(user,pass)==CHECK_OK)
	{
		AfxMessageBox("登陆成功");
	}
	C图片管理器App* thisapp = ((C图片管理器App*)AfxGetApp());
 	thisapp->CurrentUser = user;
	thisapp->m_LoginStatus = true;


	CDialogEx::OnOK();
}
