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
	ON_LBN_SELCHANGE(IDC_LIST1_SEARCH, &CFilesearchDlg::OnLbnSelchangeList1Search)
END_MESSAGE_MAP()


// CFilesearchDlg 消息处理程序

//开始搜索
void CFilesearchDlg::OnBnClickedButtonStartsearch()
{
	// TODO: 在此添加控件通知处理程序代码
	m_file.ResetContent();
	CString str;
	m_keyword.GetWindowTextA(str);                           //搜索关键字
	if (str=="")                                  //未输入关键字
	{
		AfxMessageBox("请输入关键字");
		return;
	}
	searchado.OnInitADOConn("权限");                         //查询文件权限
	searchado.m_pRecordset->MoveFirst();                       //遍历数据库
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

//搜索列表
void CFilesearchDlg::OnLbnDblclkList1Search()                      
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_file.GetCurSel() == -1)
	{
		return;
	}
	CString str;
	m_file.GetText(m_file.GetCurSel(),str);                               //展示搜索出的文件
	((C图片管理器App*)AfxGetApp())->OnCerTainFileOpen(str);
	OnCancel();



}


void CFilesearchDlg::OnLbnSelchangeList1Search()
{
	// TODO: 在此添加控件通知处理程序代码
	CImage img;
	CString str;
	m_file.GetText(m_file.GetCurSel(),str);
	img.Load(str);
	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_STATIC_PICTURE);
	CDC *pDC = pWnd->GetDC();
	pWnd->GetClientRect(&rect);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	img.Draw(pDC->m_hDC,rect);
	ReleaseDC( pDC );

}
