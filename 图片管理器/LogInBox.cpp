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
END_MESSAGE_MAP()


// LogInBox 消息处理程序


void LogInBox::OnBnClickedNewclient()
{
	
	NewClientBox ncb;
	ncb.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
