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
	ON_BN_CLICKED(IDOK, &LogInBox::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &LogInBox::OnBnClickedButtonExit)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// LogInBox ��Ϣ�������


void LogInBox::OnBnClickedNewclient()
{
	
	NewClientBox ncb;
	if (ncb.DoModal()==IDOK){
	
	ado.OnInitADOConn("�û�");
	ado.NewUser(ncb.m_user,ncb.m_pass);
	ado.ExitConnect();
	
	
	}
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


int LogInBox::CheckState(CString& name, CString& pass)
{
		bool userexist = false;
		bool passwordright = false;
		ado.OnInitADOConn("�û�");
		ado.m_pRecordset->MoveFirst();
		while (!ado.m_pRecordset->adoEOF)
		{
			if (name.Compare((_bstr_t)(ado.m_pRecordset->GetCollect("�û���")))==0)
			{
				userexist = true;
				if (pass.Compare((_bstr_t)(ado.m_pRecordset->GetCollect("����")))==0)
				{
					passwordright = true;
					break;
				}
			}
			ado.m_pRecordset->MoveNext();
		}
		ado.m_pRecordset->MoveFirst();
	

		ado.ExitConnect();
	

	if (userexist)
		 if (passwordright) return CHECK_OK;
		 else return WRONG_PASSWORD;
	else
		return NO_USER;
	return 0;
}


void LogInBox::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CString user;
	CString pass;
	GetDlgItem(IDC_EDIT_LOGINUSERNAME)->GetWindowText(user);
	GetDlgItem(IDC_EDIT_LOGINPASS)->GetWindowText(pass);
	if ((user=="")||(pass=="")) 
	{
		AfxMessageBox("�û��������벻��Ϊ��");
		return ;
	}
	if (CheckState(user,pass)==WRONG_PASSWORD)
	{
		AfxMessageBox("�������");
		return ;
	}

	if (CheckState(user,pass)==NO_USER)
	{
		AfxMessageBox("�û�������");
		return ;
	}
	if (CheckState(user,pass)==CHECK_OK)
	{
		AfxMessageBox("��½�ɹ�");
	}
	CͼƬ������App* thisapp = ((CͼƬ������App*)AfxGetApp());
 	thisapp->CurrentUser = user;
	thisapp->m_LoginStatus = true;


	CDialogEx::OnOK();
}


void LogInBox::OnBnClickedButtonExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExitProcess( -1 );
}


void LogInBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CRect rc;
	GetClientRect(&rc);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_DLGBKG);

	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0,0,rc.Width(), rc.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);


	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


BOOL LogInBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*
	SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
	GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	HINSTANCE hInst = LoadLibrary("User32.DLL"); 
	if(hInst) 
			 { 
			typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
			MYFUNC fun = NULL;
			fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
			if(fun)
			fun(this->GetSafeHwnd(),0,200,2); 
			FreeLibrary(hInst); 
			}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	*/
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
