// CommandDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "图片管理器.h"
#include "CommandDlg.h"
#include "afxdialogex.h"


// CommandDlg 对话框

IMPLEMENT_DYNAMIC(CommandDlg, CDialogEx)

CommandDlg::CommandDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CommandDlg::IDD, pParent)
{

}

CommandDlg::~CommandDlg()
{
}

void CommandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CommandDlg, CDialogEx)
END_MESSAGE_MAP()


// CommandDlg 消息处理程序
