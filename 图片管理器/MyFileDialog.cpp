#include "stdafx.h"
#include "MyFileDialog.h"


IMPLEMENT_DYNAMIC(CMyFileDialog, CFileDialog)
	CMyFileDialog::CMyFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
	DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd): CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

void CMyFileDialog::DoDataExchange(CDataExchange* pDX)
{
	//CMyFileDialog::DoDataExchange(pDX);
}

CMyFileDialog::~CMyFileDialog(void)
{
}



BEGIN_MESSAGE_MAP(CMyFileDialog, CFileDialog)
	
//	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()




BOOL CMyFileDialog::OnInitDialog()
{
	CFileDialog::OnInitDialog();
	return TRUE;
}



//void CMyFileDialog::OnRButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	return
//	CFileDialog::OnRButtonDown(nFlags, point);
//}


void CMyFileDialog::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MessageBox("hello");
	CFileDialog::OnRButtonUp(nFlags, point);
}


BOOL CMyFileDialog::PreTranslateMessage(MSG* pMsg)
{
	if (WM_RBUTTONDOWN == pMsg->message)
	{
		MessageBox("hello");
	}
	return CDialog::PreTranslateMessage(pMsg);

}



void CMyFileDialog::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	MessageBox("HI");
	return;
	// TODO: 在此处添加消息处理程序代码
}
