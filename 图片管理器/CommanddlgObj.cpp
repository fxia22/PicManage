#include "stdafx.h"
#include "ͼƬ������.h"
#include "CommandDlgObj.h"
#include "afxdialogex.h"


// CommandDlgObj �Ի���

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


// CommandDlgObj ��Ϣ�������
