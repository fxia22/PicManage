// LogInBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "LogInBox.h"
#include "afxdialogex.h"
#include "NewClientBox.h"


// LogInBox �Ի���

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


// LogInBox ��Ϣ�������


void LogInBox::OnBnClickedNewclient()
{
	
	NewClientBox ncb;
	ncb.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
