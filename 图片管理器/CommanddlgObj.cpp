#include "stdafx.h"
#include "图片管理器.h"
#include "CommandDlgObj.h"
#include "afxdialogex.h"


// CommandDlgObj 对话框

IMPLEMENT_DYNAMIC(CommandDlgObj, CDialogEx)

CommandDlgObj::CommandDlgObj(CWnd* pParent /*=NULL*/)
	: CDialogEx(CommandDlgObj::IDD, pParent)
{

}

CommandDlgObj::~CommandDlgObj()
{
}

void CommandDlgObj::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CommandDlgObj, CDialogEx)
END_MESSAGE_MAP()


// CommandDlgObj 消息处理程序
