
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "ͼƬ������.h"
#include "ͼƬ������Doc.h"
#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
//���ĵ���Ϣӳ��

	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	CMainFrame* pmain = (CMainFrame*)AfxGetMainWnd();
	pmain->m_ChildFramePtrList.AddHead( this );
	
	// TODO: �ڴ���ӳ�Ա��ʼ������
	}

CChildFrame::~CChildFrame()
{
	CMainFrame* pmain = (CMainFrame*)AfxGetMainWnd();
	POSITION pos = pmain->m_ChildFramePtrList.Find( this );
	if ( pos != NULL )
	{
		pmain->m_ChildFramePtrList.RemoveAt( pos );
	}
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style &= ~WS_THICKFRAME;
	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_MINIMIZEBOX;
	cs.lpszClass = AfxRegisterWndClass(0);
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������


void CChildFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if (!((CͼƬ������Doc*)GetActiveDocument())->IsEmpty())
		{
			if (MessageBox("��û�б��棬ȷ��Ҫ�˳���",((CͼƬ������Doc*)GetActiveDocument())->GetTitle(),MB_OKCANCEL)==IDOK);
			else return ;
	}
	CMDIChildWnd::OnClose();
}


void CChildFrame::ExitWithoutQuery(void)
{
		CMDIChildWnd::OnClose();
}
