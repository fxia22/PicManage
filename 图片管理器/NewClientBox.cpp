// NewClientBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "NewClientBox.h"
#include "afxdialogex.h"


// NewClientBox �Ի���

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


// NewClientBox ��Ϣ�������
