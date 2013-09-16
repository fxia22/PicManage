// SizeDlg.cpp : 实现文件
//
/************************************************************************/
/* 更改画布大小的对话框的实现
Edit by xf
*/
/************************************************************************/
#include "stdafx.h"
#include "图片管理器.h"
#include "SizeDlg.h"
#include "afxdialogex.h"


// CSizeDlg 对话框

IMPLEMENT_DYNAMIC(CSizeDlg, CDialogEx)

CSizeDlg::CSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSizeDlg::IDD, pParent)
{

	width = 0;
	height = 0;
}

CSizeDlg::~CSizeDlg()
{
}

void CSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_height);
	DDX_Control(pDX, IDC_EDIT2_SIZE, m_width);
}


BEGIN_MESSAGE_MAP(CSizeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSizeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSizeDlg 消息处理程序

/************************************************************************/
/* 
点击ok，将数据存到对话框类私有成员中，
供父框架访问
*/
/************************************************************************/
void CSizeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString widthstring,heightstring;
	GetDlgItem(IDC_EDIT_SIZE)->GetWindowTextA(heightstring);
	GetDlgItem(IDC_EDIT2_SIZE)->GetWindowTextA(widthstring);
	height = atoi(heightstring.GetBuffer());
	width  = atoi(widthstring.GetBuffer());
	if ((height>0)&&(height<=600)&&(width>0)&&(width<=900))
	CDialogEx::OnOK();
	else
	{
		MessageBox("请保证画布大小在900*600之内");
		return;
	}
}
