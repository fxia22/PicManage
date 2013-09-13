#include "stdafx.h"
#include "ClientWnd.h"
#include "Resource.h"

CClientWnd::CClientWnd(void)
{
}


CClientWnd::~CClientWnd(void)
{
}
BEGIN_MESSAGE_MAP(CClientWnd, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CClientWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rectbk; // 客户区的大小 
	CDC dcMen; // 内存设备描述表 [
	CBitmap bmbk; // 位图对象 
	bmbk.LoadBitmap(IDB_BITMAP_BKGG); // 从资源加载位图 bitmap 
	BITMAP stBitmap; 
	bmbk.GetObject(sizeof(BITMAP),&stBitmap); 
	CSize bmsize(stBitmap.bmWidth,stBitmap.bmHeight); 
	dcMen.CreateCompatibleDC(pDC); // 创建兼容的设备描述表 
	CBitmap *pold=dcMen.SelectObject(&bmbk); 
	GetClientRect(&rectbk); 
	pDC->StretchBlt(rectbk.left,rectbk.top,rectbk.Width(), 
	rectbk.Height(),&dcMen,0,0,bmsize.cx,bmsize.cy,SRCCOPY); 
	dcMen.SelectObject(pold); 
	dcMen.DeleteDC(); 
	return true; 

}


void CClientWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	Invalidate(); 
	// TODO: 在此处添加消息处理程序代码
}

WNDPROC* CClientWnd::GetSuperWndProcAddr() 
{
	static WNDPROC NEAR pfnSuper = NULL; 
	return &pfnSuper; // 返回函数指针 
}

