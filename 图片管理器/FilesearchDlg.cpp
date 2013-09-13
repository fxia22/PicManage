// FilesearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "FilesearchDlg.h"
#include "afxdialogex.h"


// CFilesearchDlg �Ի���

IMPLEMENT_DYNAMIC(CFilesearchDlg, CDialogEx)

CFilesearchDlg::CFilesearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFilesearchDlg::IDD, pParent)
{

}

CFilesearchDlg::~CFilesearchDlg()
{
}

void CFilesearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILESEACH, m_keyword);
	DDX_Control(pDX, IDC_LIST1_SEARCH, m_file);
}


BEGIN_MESSAGE_MAP(CFilesearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_STARTSEARCH, &CFilesearchDlg::OnBnClickedButtonStartsearch)
	ON_LBN_DBLCLK(IDC_LIST1_SEARCH, &CFilesearchDlg::OnLbnDblclkList1Search)
END_MESSAGE_MAP()


// CFilesearchDlg ��Ϣ�������


void CFilesearchDlg::OnBnClickedButtonStartsearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_file.ResetContent();
	CString str;
	m_keyword.GetWindowTextA(str);
	if (str=="")
	{
		AfxMessageBox("������ؼ���");
		return;
	}
	searchado.OnInitADOConn("Ȩ��");
	searchado.m_pRecordset->MoveFirst();
	while (!searchado.m_pRecordset->adoEOF)
	{
		CString filename;
		filename = (LPCTSTR)(_bstr_t)(searchado.m_pRecordset->GetCollect("�ļ�·��"));
		if (filename.Find(str)!=-1)
			m_file.AddString(filename);
		searchado.m_pRecordset->MoveNext();
	}
	searchado.m_pRecordset->MoveFirst();
	searchado.ExitConnect();

}


void CFilesearchDlg::OnLbnDblclkList1Search()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_file.GetCurSel() == -1)
	{
		return;
	}
	CString str;
	m_file.GetText(m_file.GetCurSel(),str);
	((CͼƬ������App*)AfxGetApp())->OnCerTainFileOpen(str);
	OnCancel();



}
