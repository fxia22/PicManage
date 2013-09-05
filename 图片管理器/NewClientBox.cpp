// NewClientBox.cpp : 实现文件
//

#include "stdafx.h"
#include "图片管理器.h"
#include "NewClientBox.h"
#include "afxdialogex.h"


// NewClientBox 对话框

IMPLEMENT_DYNAMIC(NewClientBox, CDialogEx)

NewClientBox::NewClientBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewClientBox::IDD, pParent)
{

}

NewClientBox::~NewClientBox()
{
}

void NewClientBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewClientBox, CDialogEx)
END_MESSAGE_MAP()


// NewClientBox 消息处理程序
