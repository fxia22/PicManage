// AdminDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "图片管理器.h"
#include "AdminDlg.h"
#include "afxdialogex.h"


// CAdminDlg 对话框

IMPLEMENT_DYNAMIC(CAdminDlg, CDialogEx)

CAdminDlg::CAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdminDlg::IDD, pParent)
{

}

CAdminDlg::~CAdminDlg()
{
}

void CAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdminDlg, CDialogEx)
END_MESSAGE_MAP()


// CAdminDlg 消息处理程序
