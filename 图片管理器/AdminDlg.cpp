// AdminDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "AdminDlg.h"
#include "afxdialogex.h"
using namespace std;

// CAdminDlg �Ի���

IMPLEMENT_DYNAMIC(CAdminDlg, CDialogEx)

CAdminDlg::CAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdminDlg::IDD, pParent)
{

	m_username = _T("");
	m_sudo = _T("");
	m_pathname = _T("");
	m_current_operator = _T("");
}

CAdminDlg::~CAdminDlg()
{
}

void CAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST_USERSELECT, m_List_user);
	//  DDX_Control(pDX, IDC_LIST_SUDOCTRL, m_List_sudo);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_filepath);
	DDX_Control(pDX, IDC_LIST_TEST, m_List_sudo2);
	DDX_Control(pDX, IDC_LIST_USER2, m_List_user2);
}


BEGIN_MESSAGE_MAP(CAdminDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CAdminDlg::OnBnClickedButtonOpenFile)
	ON_LBN_SELCHANGE(IDC_LIST_TEST, &CAdminDlg::OnLbnSelchangeListTest)
	ON_LBN_SELCHANGE(IDC_LIST_USER2, &CAdminDlg::OnLbnSelchangeListUser2)
	ON_BN_CLICKED(IDOK, &CAdminDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAdminDlg ��Ϣ�������


void CAdminDlg::OnBnClickedButtonOpenFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"bmp��ʽ (*.bmp)|*.bmp||",NULL);
	if (fdlg.DoModal()==IDOK)
	{
		m_pathname = fdlg.GetPathName();
		GetDlgItem(IDC_EDIT_FILEPATH)->SetWindowText(m_pathname);
	}
}


BOOL CAdminDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	  m_List_sudo2.AddString("дȨ��");
	  m_List_sudo2.AddString("��Ȩ��");
	  m_sudo = "";
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	  adminado.OnInitADOConn("�û�");
	  adminado.m_pRecordset->MoveFirst();
	  while (!adminado.m_pRecordset->adoEOF)
	  {
		CString temp = (_bstr_t)(adminado.m_pRecordset->GetCollect("�û���"));
		//userlist.push_back(temp);
		m_List_user2.AddString(temp);
		adminado.m_pRecordset->MoveNext();
	  }
	  adminado.m_pRecordset->MoveFirst();
	  adminado.ExitConnect();

	  m_current_operator  = ((CͼƬ������App*)AfxGetApp())->CurrentUser;





	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAdminDlg::OnLbnSelchangeListTest()
{
		
	if (m_List_sudo2.GetCurSel()==0) m_sudo= "��";
	else if (m_List_sudo2.GetCurSel()==1) m_sudo = "д";
}


void CAdminDlg::OnLbnSelchangeListUser2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_List_user2.GetText(m_List_user2.GetCurSel(),m_username);
	
}


void CAdminDlg::OnBnClickedOk()
{
	int state;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pathname=="") 
	{
		AfxMessageBox("��ѡ���ļ�");
		return;
	}

	if (m_sudo=="") 
	{
		AfxMessageBox("��ѡ��Ȩ��");
		return;
	}
	if (m_username=="") 
	{
		AfxMessageBox("��ѡ���û�");
		return;
	}
	state = adminado.CheckFileState(m_current_operator,m_pathname);
	
	if (state!=Adomdb::CAN_WRITE)
	{
		AfxMessageBox("�����ڸ��ļ�û��дȨ��");
		return;
	}
	if (m_current_operator==m_username)
	{
		AfxMessageBox("�����ܸ��Լ���Ȩ");
		return;
	}
	adminado.OnInitADOConn("Ȩ��");
	adminado.NewFile(m_username,m_pathname,m_sudo);
	adminado.ExitConnect();
	AfxMessageBox("��Ȩ�ɹ�");
	return;
	CDialogEx::OnOK();
}
