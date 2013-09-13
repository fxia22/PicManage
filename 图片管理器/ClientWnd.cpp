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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rectbk; // �ͻ����Ĵ�С 
	CDC dcMen; // �ڴ��豸������ [
	CBitmap bmbk; // λͼ���� 
	bmbk.LoadBitmap(IDB_BITMAP_BKGG); // ����Դ����λͼ bitmap 
	BITMAP stBitmap; 
	bmbk.GetObject(sizeof(BITMAP),&stBitmap); 
	CSize bmsize(stBitmap.bmWidth,stBitmap.bmHeight); 
	dcMen.CreateCompatibleDC(pDC); // �������ݵ��豸������ 
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
	// TODO: �ڴ˴������Ϣ����������
}

WNDPROC* CClientWnd::GetSuperWndProcAddr() 
{
	static WNDPROC NEAR pfnSuper = NULL; 
	return &pfnSuper; // ���غ���ָ�� 
}

