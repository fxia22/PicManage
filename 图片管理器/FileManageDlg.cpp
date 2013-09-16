// FileManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "FileManageDlg.h"
#include "afxdialogex.h"


// CFileManageDlg �Ի���

IMPLEMENT_DYNAMIC(CFileManageDlg, CDialogEx)

CFileManageDlg::CFileManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileManageDlg::IDD, pParent)
{

	m_currentuser = _T("");
	currentfile = _T("");
	currentsudo = _T("");
	currentgroup = _T("");
}

CFileManageDlg::~CFileManageDlg()
{
}

void CFileManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VISIBLEFILE, m_VisibleFile);
	DDX_Control(pDX, IDC_LIST_FILEGROUP, m_Group);
	DDX_Control(pDX, IDC_LIST_FILE_IN_GROUP, m_FileInGroup);
	DDX_Control(pDX, IDC_EDIT_ADDGROUP, m_Groupname);
}


BEGIN_MESSAGE_MAP(CFileManageDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDGROUP, &CFileManageDlg::OnBnClickedButtonAddgroup)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TO_GROUP, &CFileManageDlg::OnBnClickedButtonAddToGroup)
	ON_LBN_SELCHANGE(IDC_LIST_VISIBLEFILE, &CFileManageDlg::OnLbnSelchangeListVisiblefile)
	ON_LBN_SELCHANGE(IDC_LIST_FILEGROUP, &CFileManageDlg::OnLbnSelchangeListFilegroup)
	ON_LBN_DBLCLK(IDC_LIST_FILE_IN_GROUP, &CFileManageDlg::OnLbnDblclkListFileInGroup)
	ON_LBN_DBLCLK(IDC_LIST_VISIBLEFILE, &CFileManageDlg::OnLbnDblclkListVisiblefile)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEFILE, &CFileManageDlg::OnBnClickedButtonRemovefile)
END_MESSAGE_MAP()


// CFileManageDlg ��Ϣ�������


void CFileManageDlg::OnBnClickedButtonAddgroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_Groupname.GetWindowTextA(str);
	if (str!="")
	{
		m_Groupname.SetWindowText("");
		m_Group.AddString(str);
	}
}



BOOL CFileManageDlg::OnInitDialog()
{
	CString du = "��";
	CDialogEx::OnInitDialog();
	m_currentuser = ((CͼƬ������App*)AfxGetApp())->CurrentUser;
	fileado.OnInitADOConn("Ȩ��");
	fileado.m_pRecordset->MoveFirst();
	while (!fileado.m_pRecordset->adoEOF)
	{
		if (m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("�û���")))==0)
		{
			CString name = (_bstr_t)(fileado.m_pRecordset->GetCollect("�ļ�·��"));
			if (du.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("����Ȩ��")))==0)
				name+="(ֻ��)";
			if (m_VisibleFile.FindString(-1,name)==-1)
			{m_VisibleFile.AddString(name);
			}
			
		}
		fileado.m_pRecordset->MoveNext();
	}
	fileado.m_pRecordset->MoveFirst();
	fileado.ExitConnect();


	fileado.OnInitADOConn("ͼƬ��");
	fileado.m_pRecordset->MoveFirst();
	while (!fileado.m_pRecordset->adoEOF)
	{
		if (m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("�û���")))==0)
		{
			CString group =  (_bstr_t)(fileado.m_pRecordset->GetCollect("ͼƬ��"));
			if (m_Group.FindString(-1,group)==-1)m_Group.AddString(group);
		}
		fileado.m_pRecordset->MoveNext();
	}
	fileado.m_pRecordset->MoveFirst();
	fileado.ExitConnect();





	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CFileManageDlg::OnBnClickedButtonAddToGroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ((currentfile=="")||(currentgroup==""))
	{
		AfxMessageBox("��ѡ����");
		return;
	}
	fileado.OnInitADOConn("ͼƬ��");
	fileado.NewFileToGroup(m_currentuser,currentfile,currentsudo,currentgroup);
	fileado.ExitConnect();

	fileado.OnInitADOConn("ͼƬ��");
	fileado.m_pRecordset->MoveFirst();
	while (!fileado.m_pRecordset->adoEOF)
	{
		if ((m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("�û���")))==0)&& (currentgroup.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("ͼƬ��")))==0))
		{
			CString name =  (_bstr_t)(fileado.m_pRecordset->GetCollect("�ļ�·��"));
			if (m_FileInGroup.FindString(-1,name)==-1)
			{
				m_FileInGroup.AddString(name);
			}

		}
		fileado.m_pRecordset->MoveNext();
	}
	fileado.m_pRecordset->MoveFirst();
	fileado.ExitConnect();

	
}


void CFileManageDlg::OnLbnSelchangeListVisiblefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_VisibleFile.GetText(m_VisibleFile.GetCurSel(),str);
	if (str.Find("ֻ��")!=-1) 
		{currentsudo ="��";
		currentfile = str.Left(str.GetLength()-6);
	
	}
	else {
		currentsudo = "д";
		currentfile = str;
	}

}


void CFileManageDlg::OnLbnSelchangeListFilegroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 m_Group.GetText(m_Group.GetCurSel(),currentgroup);
	 m_FileInGroup.ResetContent();
	 //AfxMessageBox(currentgroup);
	 fileado.OnInitADOConn("ͼƬ��");
	 fileado.m_pRecordset->MoveFirst();
	 while (!fileado.m_pRecordset->adoEOF)
	 {
		 if ((m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("�û���")))==0)&& (currentgroup.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("ͼƬ��")))==0))
		 {
			 CString name =  (_bstr_t)(fileado.m_pRecordset->GetCollect("�ļ�·��"));
			if (m_FileInGroup.FindString(-1,name)==-1)
			{
					m_FileInGroup.AddString(name);
			}
		
		 }
		 fileado.m_pRecordset->MoveNext();
	 }
	 fileado.m_pRecordset->MoveFirst();
	 fileado.ExitConnect();
}



void CFileManageDlg::OnLbnDblclkListFileInGroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_FileInGroup.GetCurSel() == -1)
	{
		return;
	}
	CString str;
	m_FileInGroup.GetText(m_FileInGroup.GetCurSel(),str);
	((CͼƬ������App*)AfxGetApp())->OnCerTainFileOpen(str);
	OnCancel();
}


void CFileManageDlg::OnLbnDblclkListVisiblefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_VisibleFile.GetCurSel() == -1)
	{
		return;
	}
	CString str;
	m_VisibleFile.GetText(m_VisibleFile.GetCurSel(),str);
	((CͼƬ������App*)AfxGetApp())->OnCerTainFileOpen(str);
	OnCancel();


}


void CFileManageDlg::OnBnClickedButtonRemovefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (currentsudo =="��")
	{
		AfxMessageBox("���Ը��ļ�ֻ�ж�Ȩ�ޣ�����ɾ��");
		return;
	}

	else
	{
		CFile::Remove(currentfile);
		fileado.OnInitADOConn("Ȩ��");
		fileado.m_pRecordset->MoveFirst();
		while (!fileado.m_pRecordset->adoEOF)
		{
			
				CString name =  (_bstr_t)(fileado.m_pRecordset->GetCollect("�ļ�·��"));
				if (name==currentfile)
				{
					fileado.m_pRecordset->Delete(adAffectCurrent);
					fileado.m_pRecordset->Update();
					fileado.ExitConnect();
					break;
				}
				fileado.m_pRecordset->MoveNext();

			}
			
		AfxMessageBox("�ļ�ɾ���ɹ�!");


		m_VisibleFile.ResetContent();
		CString du = "��";
		fileado.OnInitADOConn("Ȩ��");
		fileado.m_pRecordset->MoveFirst();
		while (!fileado.m_pRecordset->adoEOF)
		{
			if (m_currentuser.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("�û���")))==0)
			{
				CString name = (_bstr_t)(fileado.m_pRecordset->GetCollect("�ļ�·��"));
				if (du.Compare((_bstr_t)(fileado.m_pRecordset->GetCollect("����Ȩ��")))==0)
					name+="(ֻ��)";
				if (m_VisibleFile.FindString(-1,name)==-1)
				{m_VisibleFile.AddString(name);
				}

			}
			fileado.m_pRecordset->MoveNext();
		}
		fileado.m_pRecordset->MoveFirst();
		fileado.ExitConnect();

	}







}
