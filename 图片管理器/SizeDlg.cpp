// SizeDlg.cpp : ʵ���ļ�
//
/************************************************************************/
/* ���Ļ�����С�ĶԻ����ʵ��
Edit by xf
*/
/************************************************************************/
#include "stdafx.h"
#include "ͼƬ������.h"
#include "SizeDlg.h"
#include "afxdialogex.h"


// CSizeDlg �Ի���

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


// CSizeDlg ��Ϣ�������

/************************************************************************/
/* 
���ok�������ݴ浽�Ի�����˽�г�Ա�У�
������ܷ���
*/
/************************************************************************/
void CSizeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString widthstring,heightstring;
	GetDlgItem(IDC_EDIT_SIZE)->GetWindowTextA(heightstring);
	GetDlgItem(IDC_EDIT2_SIZE)->GetWindowTextA(widthstring);
	height = atoi(heightstring.GetBuffer());
	width  = atoi(widthstring.GetBuffer());
	if ((height>0)&&(height<=600)&&(width>0)&&(width<=900))
	CDialogEx::OnOK();
	else
	{
		MessageBox("�뱣֤������С��900*600֮��");
		return;
	}
}
