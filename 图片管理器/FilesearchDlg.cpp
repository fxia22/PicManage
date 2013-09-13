// FilesearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "图片管理器.h"
#include "FilesearchDlg.h"
#include "afxdialogex.h"


// CFilesearchDlg 对话框

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


// CFilesearchDlg 消息处理程序


void CFilesearchDlg::OnBnClickedButtonStartsearch()
{
	// TODO: 在此添加控件通知处理程序代码
	m_file.ResetContent();
	CString str;
	m_keyword.GetWindowTextA(str);
	if (str=="")
	{
		AfxMessageBox("请输入关键字");
		return;
	}
	searchado.OnInitADOConn("权限");
	searchado.m_pRecordset->MoveFirst();
	while (!searchado.m_pRecordset->adoEOF)
	{
		CString filename;
		filename = (LPCTSTR)(_bstr_t)(searchado.m_pRecordset->GetCollect("文件路径"));
		if (filename.Find(str)!=-1)
			m_file.AddString(filename);
		searchado.m_pRecordset->MoveNext();
	}
	searchado.m_pRecordset->MoveFirst();
	searchado.ExitConnect();

}


void CFilesearchDlg::OnLbnDblclkList1Search()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_file.GetCurSel() == -1)
	{
		return;
	}
	CString str;
	m_file.GetText(m_file.GetCurSel(),str);
	((C图片管理器App*)AfxGetApp())->OnCerTainFileOpen(str);
	OnCancel();



}
