// NewClientBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "NewClientBox.h"
#include "afxdialogex.h"
#include "LogInBox.h"

// NewClientBox �Ի���

IMPLEMENT_DYNAMIC(NewClientBox, CDialogEx)

NewClientBox::NewClientBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewClientBox::IDD, pParent)
{

	m_user = _T("");
	m_pass = _T("");
}

NewClientBox::~NewClientBox()
{
}

void NewClientBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USERNAME, username);
	DDX_Control(pDX, IDC_EDIT_PASS1, password1);
	DDX_Control(pDX, IDC_EDIT_PASS2, password2);
}


BEGIN_MESSAGE_MAP(NewClientBox, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewClientBox::OnBnClickedOk)
END_MESSAGE_MAP()


// NewClientBox ��Ϣ�������


void NewClientBox::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_PASS1)->GetWindowText(m_pass);
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(m_user);
	CString pass;
	GetDlgItem(IDC_EDIT_PASS2)->GetWindowText(pass);
	if ((m_user=="")||(m_pass=="")) 
	{
		AfxMessageBox("�û��������벻��Ϊ��");
		return ;
	}
	if (m_pass.Compare(pass)!=0) 
		{AfxMessageBox("�����������벻һ��");
		return ;
	}
	LogInBox* pd = (LogInBox*)GetParent();
	if (pd->CheckState(m_user,m_pass)!=LogInBox::NO_USER)
		{
			AfxMessageBox("�û�������");
		//	CString str;
		//	str.Format("%d",pd->CheckState(m_user,m_pass));
		//	AfxMessageBox(str);
			return;
	}
	CDialogEx::OnOK();
}
